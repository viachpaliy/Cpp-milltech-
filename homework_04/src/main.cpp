#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: ugv_odometry <input_path>\n";
        return 1;
    }

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

    return 0;
}
