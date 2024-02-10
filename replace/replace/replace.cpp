#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::string ReplaceString(
	const std::string& subject,
	const std::string& searchString,
	const std::string& replaceString)
{
	if (searchString == "")
	{
		return subject;
	}

	size_t pos = 0;
	std::string result = subject;
	size_t startPos = result.find(searchString);
	while (startPos != std::string::npos)
	{
		result.replace(startPos, searchString.length(), replaceString);
		startPos = result.find(searchString, startPos + replaceString.length());
	}

	return result;
}

void CopyStreamWithReplacement(
	std::istream& input,
	std::ostream& output,
	const std::string& searchString,
	const std::string& replaceString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replaceString) << "\n";
	}
}

bool CopyFileWithReplacement(
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& searchString,
	const std::string& replaceString)
{
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open " << outputFileName << " for writing\n";
		return false;
	}

	CopyStreamWithReplacement(input, output, searchString, replaceString);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (!CopyFileWithReplacement(
			args->inputFileName,
			args->outputFileName,
			args->searchString,
			args->replaceString))
	{
		return 1;
	}

	return 0;
}
