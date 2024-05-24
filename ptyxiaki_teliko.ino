#include <Wire.h>                     // It includes the necessary libraries: Wire.h for I2C communication and Adafruit_AMG88xx.h for interfacing with the AMG88xx sensor. 
#include <Adafruit_AMG88xx.h>        

//In the setup() function:
//It starts serial communication at a baud rate of 9600.
//It attempts to initialize communication with the AMG88xx sensor using amg.begin().
//If the sensor is not found, it prints an error message and enters an infinite loop.

Adafruit_AMG88xx amg;             // It initializes an instance of the Adafruit_AMG88xx class called amg.

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}

//In the loop() function:
//It reads the temperature values of all pixels in the sensor array using amg.readPixels(pixels).
//It prints the temperature values of all pixels in the sensor array to the serial monitor.
//It delays for one second before repeating the process.

void loop() { 
    //read all the pixels
    amg.readPixels(pixels);

    float sum = 0.0; // Variable to hold the sum of temperatures
    float max_temperature = -100;
    float min_temperature = 100;
    int min_position;
    int max_position;
    int j;
    float sum2 = 0.0;
    int group_count = 0;

    Serial.print("[");
    for(int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++){
        Serial.print(pixels[i]);
        Serial.print(", ");
        sum += pixels[i]; // Accumulate temperature readings
        if (pixels[i]>max_temperature){
            max_temperature = pixels[i];
            max_position = int(i);
        }
        if (pixels[i]<min_temperature){
            min_temperature = pixels[i];
            min_position = int(i);
        }
        if(i % 8 == 7) {
            Serial.println();
        }
    }

    Serial.println("]");
    Serial.println();

    // Calculate average temperature
    float averageTemperature = sum / AMG88xx_PIXEL_ARRAY_SIZE;

    Serial.print("Sum of temperatures: ");
    Serial.println(sum);
    Serial.print("Average temperature: ");
    Serial.println(averageTemperature);
    Serial.print("Maximum Temperature: ");
    Serial.println(max_temperature);
    Serial.print("In the element: ");
    Serial.println(max_position);
    Serial.print("Minimum Temperature: ");
    Serial.println(min_temperature);
    Serial.print("In the element: ");
    Serial.println(min_position);

    Serial.println();

    for(j=0; j<49; j+=16)
    {
        for(int i=0; i<7; i+=2)
        {
            sum2 += pixels[ i + j ];
            sum2 += pixels[ i + j + 1];
            sum2 += pixels[ i + j + 8 ];
            sum2 += pixels[ i + j + 9 ];
            
            float averageTemperature = sum2 / 4;
            //Serial.print("Group ");
            //Serial.print(group_count);
            //Serial.print(": ");
            //Serial.println(averageTemperature);
            group_count++;
            sum2 = 0.0;
            
        }
    }
    //Serial.println();
    //delay a second
    delay(1000);
}
