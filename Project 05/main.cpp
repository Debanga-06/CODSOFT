#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image, processed;
    string path;
    cout << "Enter image path: ";
    cin >> path;

    image = imread(path);
    if (image.empty()) {
        cout << "Could not load image!" << endl;
        return -1;
    }

    int choice;
    do {
        cout << "\n--- Image Processing Menu ---" << endl;
        cout << "1. Display Original Image\n";
        cout << "2. Convert to Grayscale\n";
        cout << "3. Apply Blur Filter\n";
        cout << "4. Apply Sharpen Filter\n";
        cout << "5. Resize Image\n";
        cout << "6. Save Processed Image\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                imshow("Original Image", image);
                waitKey(0);
                destroyAllWindows();
                break;

            case 2:
                cvtColor(image, processed, COLOR_BGR2GRAY);
                imshow("Grayscale Image", processed);
                waitKey(0);
                destroyAllWindows();
                break;

            case 3:
                GaussianBlur(image, processed, Size(7, 7), 0);
                imshow("Blurred Image", processed);
                waitKey(0);
                destroyAllWindows();
                break;

            case 4: {
                Mat kernel = (Mat_<float>(3, 3) <<
                    0, -1, 0,
                    -1, 5, -1,
                    0, -1, 0);
                filter2D(image, processed, image.depth(), kernel);
                imshow("Sharpened Image", processed);
                waitKey(0);
                destroyAllWindows();
                break;
            }

            case 5: {
                int width, height;
                cout << "Enter new width: ";
                cin >> width;
                cout << "Enter new height: ";
                cin >> height;
                resize(image, processed, Size(width, height));
                imshow("Resized Image", processed);
                waitKey(0);
                destroyAllWindows();
                break;
            }

            case 6: {
                string savePath;
                cout << "Enter filename to save: ";
                cin >> savePath;
                if (!processed.empty()) {
                    imwrite(savePath, processed);
                    cout << "Image saved as " << savePath << endl;
                } else {
                    cout << "No processed image to save!" << endl;
                }
                break;
            }

            case 0:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid option." << endl;
        }

    } while (choice != 0);

    return 0;
}
