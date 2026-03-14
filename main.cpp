#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "pixel.h"

using namespace std;

void average_colors(vector<Pixel> &pixel_list);
void flip_vertically(vector<Pixel> &pixel_list);

int main(int argc, char* argv[]) {
   vector<Pixel> pixel_list;
   
   string file_name = argv[1];
   ifstream data_file;
   data_file.open(file_name, std::ios::in);

   if (data_file.is_open()) {
      string data_line;

      while(!data_file.eof()) { //until end of the file
         getline(data_file, data_line);
         if (data_line.length() == 0) break;
         vector<string> pixel_fields;
         int prev_pos = 0;
         int last_pos = data_line.find(",");
         int index = 0; 

         //for each data field
         while(last_pos != string::npos) { 
            pixel_fields.push_back(data_line.substr(prev_pos, last_pos - prev_pos));
            prev_pos = last_pos + 1; 
            last_pos = data_line.find(",", last_pos + 1);
         }
         pixel_fields.push_back(data_line.substr(prev_pos, data_line.length() - prev_pos));

         Pixel my_pixel;
         my_pixel.x = stoi(pixel_fields[0]);
         my_pixel.y = stoi(pixel_fields[1]);
         my_pixel.r = stof(pixel_fields[2]);
         my_pixel.g = stof(pixel_fields[3]);
         my_pixel.b = stof(pixel_fields[4]);
         
         pixel_list.push_back(my_pixel);

      }

      data_file.close();
   }

   //average_colors(pixel_list);
   //cout << endl;
   flip_vertically(pixel_list);
   
   ofstream out_data;
   out_data.open("flipped.dat", std::ios::out);
   if(out_data.is_open()) {
      for (int i = 0; i < pixel_list.size(); i++) {
         out_data << pixel_list[i].x << "," << pixel_list[i].y << "," <<
            pixel_list[i].r << "," << pixel_list[i].g << "," <<
            pixel_list[i].b << endl;
      }
      out_data.close();
   } else {
      cout << "Could not open file" << endl;
   }
   

   return 0;
}

void average_colors(vector<Pixel> &pixel_list) {
   Pixel avg_pixel;
   avg_pixel.r = 0;
   avg_pixel.g = 0;
   avg_pixel.b = 0;
   
   for (int i = 0; i < pixel_list.size(); i++) {
      avg_pixel.r += pixel_list[i].r / pixel_list.size();
      avg_pixel.g += pixel_list[i].g / pixel_list.size();
      avg_pixel.b += pixel_list[i].b / pixel_list.size();
   }
   cout << avg_pixel.r << " " << avg_pixel.g << " " << avg_pixel.b << endl;
}

void flip_vertically(vector<Pixel> &pixel_list) {
   int multiplier = 0;
   double midpoint = 256 / 2;
   for (int i = 0; i < pixel_list.size(); i++) {
      pixel_list[i].y = (midpoint - pixel_list[i].y) +  midpoint;
   }
}
