#pragma once
#include "structures/_logger/logger.h"
#include <fstream>
#include "tests/test.h"

namespace gui
{
	class FileConsumer
		: public structures::ILogConsumer
	{
	public:
		FileConsumer(const std::string& filePath);
		void logMessage(structures::LogType type, const std::string& message) override;
		void logDuration(size_t size, tests::Milliseconds duration, const std::string& message);
	private: 
		std::ofstream fileStream_;
		
	};
}