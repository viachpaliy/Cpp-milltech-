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

    // TODO: implement wheel odometry for a 4-wheel differential-drive UGV.
    //
    // Parameters:
    int  ticks_per_revolution = 1024;
    double   wheel_radius_m       = 0.3;
    double   wheelbase_m          = 1.0;
    //
    // Input:  text file with 5 whitespace-separated numbers per line:
    //         timestamp_ms fl_ticks fr_ticks bl_ticks br_ticks
    // Output: same tabular format on stdout, starting from the second sample:
    //         timestamp_ms x y theta

 //  Очищення пам'яті
    delete[] timestamp_ms; delete[] fl_ticks; delete[] fr_ticks; delete[] bl_ticks; delete[] br_ticks;
    return 0;
}
