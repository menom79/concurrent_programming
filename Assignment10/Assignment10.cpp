#include <iostream>
#include <chrono>
#include <future>

using namespace std;

struct Pixel
{
    float red;
    float green;
    float blue;
};

void addPixelColors(const Pixel* image1, const Pixel* image2, Pixel* result, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        result[i].red = image1[i].red + image2[i].red;
        if (result[i].red > 1.0f)
        {
            result[i].red = 1.0f;
        }

        result[i].green = image1[i].green + image2[i].green;
        if (result[i].green > 1.0f)
        {
            result[i].green = 1.0f;
        }

        result[i].blue = image1[i].blue + image2[i].blue;
        if (result[i].blue > 1.0f)
        {
            result[i].blue = 1.0f;
        }
    }
}

Pixel* createPixels(int imageSize)
{
    Pixel* image = new Pixel[imageSize];
    for (int i = 0; i < imageSize; i++)
    {
        image[i].red = (float(rand()) / float((RAND_MAX)));
        image[i].green = (float(rand()) / float((RAND_MAX)));
        image[i].blue = (float(rand()) / float((RAND_MAX)));
    }
    return image;
}

int main()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    constexpr int imageSize = 4096 * 4096;
    Pixel* image1 = createPixels(imageSize);
    Pixel* image2 = createPixels(imageSize);
    Pixel* result = new Pixel[imageSize];

    const int numThreads = 4; // Adjust the number of threads based on your system
    const int chunkSize = imageSize / numThreads;

    // Use std::async to create asynchronous tasks for parallel execution
    vector<future<void>> futures;
    for (int i = 0; i < numThreads; ++i)
    {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? imageSize : (i + 1) * chunkSize;

        futures.push_back(async(launch::async, addPixelColors, image1, image2, result, start, end));
    }

    // Wait for all tasks to complete
    for (auto& future : futures)
    {
        future.wait();
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Execution time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]\n";

    delete[] result;
    delete[] image2;
    delete[] image1;
}
