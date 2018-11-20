//program amplifyer_filter
//author: renzhi xue 
//course: cs 472
//date:2018/11/19
//assignment:#3
//description: this program is used to amplify a wave file named test.wav. return wave file output.wav
//---------------------------------------------------------------
#include<iostream>
#include<cstdint>


using namespace std;


FILE *stream;

int main(){

	errno_t err;
	char chunk_descriptor[4], wave[4], fmt[4], data[4];
	uint32_t chunk_size, sub_chunk1_size, sample_rate, byte_rate,sub_chunk2_size;
	uint16_t audio_format, channels, block_align, bits_per_sample;
	

	err = fopen_s(&stream, "test.wav", "r"); //opening the file
	
	if (err == 0)
	{
		printf("The file 'test1.wav' was opened\n");
	}
	
	fread(chunk_descriptor, sizeof(char), 4, stream);//get the RIFF
	if (!strcmp(chunk_descriptor, "RiFF"))
	{

		cout << "error : first 4 bits are not RIFF";

	}
	fread(&chunk_size, sizeof(uint32_t), 1, stream); //get the chunk size 
	fread(wave, sizeof(char), 4, stream); //get the word wave

	if (!strcmp(wave, "WAVE"))
	{

		cout << "error :  4 bits are not WAVE";

	}
	fread(fmt, sizeof(char), 4, stream);//get the fmt 
	if (!strcmp(fmt, "fmt "))
	{

		cout << "error :  4 bits are not FMT ";

	}

	fread(&sub_chunk1_size, sizeof(uint32_t), 1, stream); //get the subchunk1size 
	fread(&audio_format, sizeof(uint16_t), 1, stream); //get hte audio format
	fread(&channels, sizeof(uint16_t), 1, stream); //get the number of channels
	fread(&sample_rate, sizeof(uint32_t), 1, stream); //get the sample rate
	fread(&byte_rate, sizeof(uint32_t), 1, stream); //get the byte rate
	fread(&block_align, sizeof(uint16_t), 1, stream); //get the block align
	fread(&bits_per_sample, sizeof(uint16_t), 1, stream);//get the bits per sample
	fread(data, sizeof(char), 4, stream); // get the word data
	if (!strcmp(data, "data "))
	{

		cout << "error :  4 bits are not data ";

	}
	fread(&sub_chunk2_size, sizeof(uint32_t), 1, stream);//get the subchunk2size
	cout << "chunk_size: " << chunk_size << endl;
	cout << "sub_trunk_size: " << sub_chunk1_size << endl;
	cout << "audio_format: " << audio_format << endl;
	cout << "channels: " << channels << endl;
	cout << "sample_rate: " << sample_rate << endl;
	cout << "byte_rate: " << byte_rate << endl;
	cout << "block_align: " << block_align << endl;
	cout << "bits_per_sample: " << bits_per_sample << endl;
	cout << "sub_chunk2_size: " << sub_chunk2_size << endl;
	// return all info gathered 
	int count = chunk_size * 8 / bits_per_sample; // get the number of total sample in the file
	short int *raw_data = new short int[count]; // create a array to catch data part of the file
	short int *temp = new short int[count]; //temp file for data processing 
	memset(raw_data, 0, sizeof(short int) * count); // sallocate space for array
	memset(temp, 0, sizeof(short int) * count);
	for (int i = 0; i < count; i++)
	{
		fread(&raw_data[i], bits_per_sample / 8, 1, stream); //put data in file into raw_data array 
		temp[i] = raw_data[i]; // passing the data to process array 
		
	}



	for (int i = 0; i < count; i++)
	{
		temp[i] = temp[i] *1.80;// amplify the audio data by multiply it by 1.80

	}





	fclose(stream); // close the input file 

	FILE *out_stream; 
	fopen_s(&out_stream, "output.wav", "w"); //open ouput file
	//write header into the out put file 
	fwrite(chunk_descriptor, sizeof(char), 4, out_stream);
	fwrite(&chunk_size, sizeof(uint32_t), 1, out_stream);
	fwrite(wave, sizeof(char), 4, out_stream);
	fwrite(fmt, sizeof(char), 4, out_stream);
	fwrite(&sub_chunk1_size, sizeof(uint32_t), 1, out_stream);
	fwrite(&audio_format, sizeof(uint16_t), 1, out_stream);
	fwrite(&channels, sizeof(uint16_t), 1, out_stream);
	fwrite(&sample_rate, sizeof(uint32_t), 1, out_stream);
	fwrite(&byte_rate, sizeof(uint32_t), 1, out_stream);
	fwrite(&block_align, sizeof(uint16_t), 1, out_stream);
	fwrite(&bits_per_sample, sizeof(uint16_t), 1, out_stream);
	fwrite(data, sizeof(char), 4, out_stream);
	fwrite(&sub_chunk2_size, sizeof(uint32_t), 1, out_stream);
	//end of writting header 

	for (int i = 0; i < count; i++)
	{
		fwrite(&temp[i], sizeof(uint16_t), 1, out_stream); // put data into the output file
	}
	fclose(out_stream);//close the file 



	system("pause");








	return 0;





}
