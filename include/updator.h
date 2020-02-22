#ifndef __UPDATOR_H
#define __UPDATOR_H

#include "Poco/Util/Application.h"
#include "Poco/Util/OptionSet.h"

#include <string>

using Poco::Util::Application;
using Poco::Util::OptionSet;

class UpdatorApplication : public Application
{
public:
	UpdatorApplication() : _helpRequested(false)
	{
	}

protected:
	void initialize(Application& self);

	void uninitialize();

	void reinitialize(Application& self);

	void defineOptions(OptionSet& options);

	void handleHelp(const std::string& name, const std::string& value);

	void handleDefine(const std::string& name, const std::string& value);

	void handleConfig(const std::string& name, const std::string& value);

	void displayHelp();

	void defineProperty(const std::string& def);

	int main(const ArgVec& args);

	void printProperties(const std::string& base);

private:
	bool _helpRequested;
};

#endif