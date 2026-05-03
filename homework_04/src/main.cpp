#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: ugv_odometry <input_path>\n";
        return 1;
    }
    std::string filename = argv[1];
 
    std::ifstream file(filename);

    if (!file.is_open()) return 1;

    // Рахуємо кількість рядків
    int lines_count = 0;
    std::string temp;
    while (std::getline(file, temp)) {
        if (!temp.empty()) lines_count++;
    }

    // Повертаємося на початок файлу
    file.clear(); 
    file.seekg(0);

    // Створюємо 5 масивів
    long* timestamp_ms = new long[lines_count];
    long* fl_ticks = new long[lines_count];
    long* fr_ticks = new long[lines_count];
    long* bl_ticks = new long[lines_count];
    long* br_ticks = new long[lines_count];

    // Зчитуємо дані
    for (int i = 0; i < lines_count; ++i) {
        file >> timestamp_ms[i] >> fl_ticks[i] >> fr_ticks[i] >> bl_ticks[i] >> br_ticks[i];
    }

  // Закриваємо файл
   file.close();

 
    // Parameters:
    int  ticks_per_revolution = 1024;
    double   wheel_radius_m       = 0.3;
    double   wheelbase_m          = 1.0;
    //
	double x = 0;
	double y = 0;
	double theta = 0;

	for (int i = 1; i < lines_count; i++)
	{
		// Delta iмпульсiв по кожному колесу:
		int d_fl = fl_ticks[i] - fl_ticks[i - 1];
		int d_fr = fr_ticks[i] - fr_ticks[i - 1];
		int d_bl = bl_ticks[i] - bl_ticks[i - 1];
		int d_br = br_ticks[i] - br_ticks[i - 1];

		// Усереднити борти
		double d_left = (d_fl + d_bl) / 2;
		double d_right = (d_fr + d_br) / 2;

		//Перевести iмпульси у метри:

		double distance_per_tick = 2 * M_PI * wheel_radius_m / ticks_per_revolution;
		double dL = d_left * distance_per_tick;
		double dR = d_right * distance_per_tick;

		//Скiльки пройшов центр робота i на скiльки повернувся:

		double d = (dL + dR) / 2; // пройдена вiдстань центру

		double dtheta = (dR - dL) / wheelbase_m; // змiна орiєнтацiї

		//Оновлення позицiї:
		x += d * cos(theta + dtheta / 2);
		y += d * sin(theta + dtheta / 2);
		theta += dtheta;
		std::cout << "\t" << std::left ;
		std::cout<< std::setw(10)  << timestamp_ms[i];
		std::cout  << std::setw(10) << x ; 
		std::cout  << std::setw(10) << y ; 
		std::cout  << std::setw(10) << theta << std::endl;
	}


 //  Очищення пам'яті
    delete[] timestamp_ms; delete[] fl_ticks; delete[] fr_ticks; delete[] bl_ticks; delete[] br_ticks;
    return 0;
}
