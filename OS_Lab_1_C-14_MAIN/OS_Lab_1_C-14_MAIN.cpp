#include <iostream>
#include <fstream>
#include "../Employee.h"
#include <string>
#include <string.h>
#include <boost/process.hpp>
#include <boost/process/io.hpp>
#include <boost/process/windows.hpp>

#pragma warning (disable:4996)

/*
Написать консольную программу Main и две утилиты (служебные программы)
Creator и Reporter, которые выполняют следующие действия.
Утилита Creator создает бинарный файл, имя которого и количество записей в котором
получает через командную строку.

remember, now ONLY with STD))
Всё работает в одном окне
*/

namespace BP = ::boost::process;

int main()
{
	setlocale(LC_ALL, "Russian");
	try
	{
		// Input for Creator
		int emount = 0;
		std::cout << "input number of elements: ";
		std::cin >> emount;
		std::string file_name;
		std::cout << "input name of binary file (it will be created): ";
		std::cin >> file_name;

		// Creator work

		std::string CreatorAllocation("C:\\AA__DISK__D\\A_WORK_WORK\\C++_2kyrs_3sem\\OS_LABs\\OS_Lab_1\\x64\\Debug\\Creator.exe");

		std::string args;
		args += CreatorAllocation + " ";
		args += file_name + " ";
		args += std::to_string(emount);

		// создаем Creator
		BP::child Creator{ args };

		std::cout << "---Creator Works---" << std::endl;

		Creator.wait(); // ждем завершения Creator
		std::cout << "---Creator ends Work---" << std::endl;

		// Вывод бинарника на консоль
		std::ifstream first_check(file_name);
		employee inputter;

		first_check.read(reinterpret_cast<char*>(&emount), sizeof(emount));
		for (size_t i = 0; i < emount; i++)
		{
			inputter.input_file_bin(first_check);
			std::cout << inputter;
			printf("\n");
		}
		// Конец вывода бинарника

		// Input for Reporter
		std::string report_name;
		std::cout << "input name of report file (it will be created): ";
		std::cin >> report_name;

		double PayForHour = 0;
		std::cout << "input pay for hour: ";
		std::cin >> PayForHour;

		// Reporter work
		std::string ReporterAllocation("C:\\AA__DISK__D\\A_WORK_WORK\\C++_2kyrs_3sem\\OS_LABs\\OS_Lab_1\\x64\\Debug\\Reporter.exe");

		std::string args_rep;
		args_rep += ReporterAllocation + " ";
		args_rep += file_name + " ";
		args_rep += report_name + " ";
		args_rep += std::to_string(PayForHour);

		// создаем Reporter
		BP::child Reporter{ args_rep };

		std::cout << "---Reporter Works---" << std::endl;

		Reporter.wait(); // ждем завершения Reporter
		std::cout << "---Reporter ends Work---" << std::endl;

		// вывод {report_name} txt файла
		std::ifstream second_check(report_name);
		employee inputter_rep;

		for (size_t i = 0; i < emount; i++)
		{
			second_check >> inputter_rep;
			double salary = 0;
			second_check >> salary;

			std::cout << inputter_rep;
			std::cout << salary;
			std::cout << std::endl;
		}

		// конец вывода {report_name} txt файла

	}
	catch (BP::process_error RE)
	{
		std::cout << RE.what();
	}
	return 0;
}