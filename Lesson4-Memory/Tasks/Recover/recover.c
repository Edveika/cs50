#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
/*
TODO:
1. Open image file
2. Look for beginning of a JPEG file. First three bytes: 0xff 0xd8 0xff. Fourth(one of those): 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef
3. Create new JPEG image
4. Write 512 bytes into it until new JPEG is found by checking first bytes after 512 bytes

filename logic: sprintf(filename, "%03i.jpg", 2);
*/

char cur_filename[7] = {'0','0','0','.','j','p','g'};;
int cur_file_name_digit = -1;
uint8_t jpg_fourth_byte[] = { 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef };

int new_jpg_found(uint8_t data[512]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE* input_file = fopen("card.raw", "r");
    if (input_file == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 2;
    }

    fseek(input_file, 0, SEEK_END);
    int file_size = ftell(input_file);
    rewind(input_file);

    FILE* cur_jpg_file = fopen(cur_filename, "w");
    int data_written_to_output = 0;

    while (data_written_to_output <= file_size)
    {
        uint8_t data[512];

        fread(data, sizeof(uint8_t), 512, input_file);

        if (new_jpg_found(data))
        {
            ++cur_file_name_digit;
            sprintf(cur_filename, "%03i.jpg", cur_file_name_digit);
            
            fclose(cur_jpg_file);
            cur_jpg_file = fopen(cur_filename, "w");
        }

        fwrite(data, sizeof(uint8_t), 512, cur_jpg_file);
        data_written_to_output += 512;
    }

    fclose(input_file);
    fclose(cur_jpg_file);

    return 0;
}

int new_jpg_found(uint8_t data[512])
{
    for (int i = 0; i < sizeof(jpg_fourth_byte); ++i)
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && data[3] == jpg_fourth_byte[i])
            return 1;

    return 0;
}