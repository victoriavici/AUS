#include "file_log_consumer.h"

gui::FileConsumer::FileConsumer(const std::string& filePath)
	: fileStream_(filePath)
{
	if (!fileStream_.is_open()) {
		throw std::logic_error("Cannot open file");
	}
}



void gui::FileConsumer::logMessage(structures::LogType type, const std::string& message)
{
	fileStream_ << structures::logTypeToString(type) << message << std::endl;
}

void gui::FileConsumer::logDuration(size_t size, tests::Milliseconds duration, const std::string& message)
{
	fileStream_ << size << ";" << duration.count() << ";" << message << std::endl;
}


