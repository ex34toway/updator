
#include "updator.h"

#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include "Poco/Message.h"

#include <iostream>
#include <sstream>

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;
using Poco::Message;


POCO_APP_MAIN(UpdatorApplication)

void UpdatorApplication::initialize(Application& self)
{
	loadConfiguration();
	Application::initialize(self);
}

void UpdatorApplication::uninitialize()
{
	Application::uninitialize();
}

void UpdatorApplication::reinitialize(Application& self)
{
	Application::reinitialize(self);
}

void UpdatorApplication::defineOptions(OptionSet& options)
{
	Application::defineOptions(options);

	options.addOption(
		Option("help", "h", "display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<UpdatorApplication>(this, &UpdatorApplication::handleHelp)));

	options.addOption(
		Option("define", "D", "define a configuration property")
		.required(false)
		.repeatable(true)
		.argument("name=value")
		.callback(OptionCallback<UpdatorApplication>(this, &UpdatorApplication::handleDefine)));

	options.addOption(
		Option("config-file", "f", "load configuration data from a file")
		.required(false)
		.repeatable(true)
		.argument("file")
		.callback(OptionCallback<UpdatorApplication>(this, &UpdatorApplication::handleConfig)));

	options.addOption(
		Option("bind", "b", "bind option value to test.property")
		.required(false)
		.repeatable(false)
		.argument("value")
		.binding("test.property"));
}

void UpdatorApplication::handleHelp(const std::string& name, const std::string& value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void UpdatorApplication::handleDefine(const std::string& name, const std::string& value)
{
	defineProperty(value);
}

void UpdatorApplication::handleConfig(const std::string& name, const std::string& value)
{
	loadConfiguration(value);
}

void UpdatorApplication::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.setHeader("Program updator");
	helpFormatter.format(std::cout);
}

void UpdatorApplication::defineProperty(const std::string& def)
{
	std::string name;
	std::string value;
	std::string::size_type pos = def.find('=');
	if (pos != std::string::npos)
	{
		name.assign(def, 0, pos);
		value.assign(def, pos + 1, def.length() - pos);
	}
	else name = def;
	config().setString(name, value);
}

int UpdatorApplication::main(const ArgVec& args)
{
	if (!_helpRequested)
	{
		if (logger().debug())
		{
			logger().debug("Command line:");
			std::ostringstream ostr;
			for (ArgVec::const_iterator it = argv().begin(); it != argv().end(); ++it)
			{
				ostr << *it << ' ';
			}
			logger().debug(ostr.str());
			logger().debug("Arguments to main():");
			for (ArgVec::const_iterator it = args.begin(); it != args.end(); ++it)
			{
				logger().debug(*it);
			}
			logger().debug("Application properties:");
			printProperties("");
		}
	}
	return Application::EXIT_OK;
}

void UpdatorApplication::printProperties(const std::string& base)
{
	AbstractConfiguration::Keys keys;
	config().keys(base, keys);
	if (keys.empty())
	{
		if (config().hasProperty(base))
		{
			std::string msg;
			msg.append(base);
			msg.append(" = ");
			msg.append(config().getString(base));
			logger().debug(msg);
		}
	}
	else
	{
		for (AbstractConfiguration::Keys::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string fullKey = base;
			if (!fullKey.empty()) fullKey += '.';
			fullKey.append(*it);
			printProperties(fullKey);
		}
	}
}