#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

#include <iostream>

int main(int, char**)
{
    std::cout << "---\n";
    std::cout << "OpenCV version : " << CV_VERSION << '\n';
    std::cout << "Major version : " << CV_MAJOR_VERSION << '\n';
    std::cout << "Minor version : " << CV_MINOR_VERSION << '\n';
    std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << '\n';
    // Read the list of transforms
    std::vector<cv::Mat> R_gripper2base, t_gripper2base;
    std::vector<cv::Mat> R_target2cam, t_target2cam;
    cv::FileStorage fs("../data.yml", cv::FileStorage::READ);
    cv::FileNode fn = fs.root();
    cv::Rect rotation_rect(0,0,3,3);
    cv::Rect translation_rect(3,0,1,3);
    for (cv::FileNodeIterator it = fn.begin(); it != fn.end(); ++it)
    {
        std::string node_name = (*it).name();
        cv::Mat T;
        fs[node_name] >> T;
        cv::Mat rotation = T(rotation_rect);
        cv::Mat translation = T(translation_rect);
        if (node_name.find("gripper2base") != std::string::npos) {
            R_gripper2base.push_back(rotation);
            t_gripper2base.push_back(translation);
        }
        else if (node_name.find("target2cam") != std::string::npos) {
            R_target2cam.push_back(rotation);
            t_target2cam.push_back(translation);
        }
    }
    std::cout << "---\n";
    std::cout << "Num of gripper2base transforms: " << R_gripper2base.size() << '\n';
    std::cout << "Num of target2cam transforms: " << R_gripper2base.size() << '\n';
    std::cout << "---\n";
    // Calibrate
    cv::Mat R_cam2gripper, t_cam2gripper;
    cv::calibrateHandEye(R_gripper2base, t_gripper2base, R_target2cam, t_target2cam, R_cam2gripper, t_cam2gripper);
    //  Output the results
    cv::Mat T_cam2gripper = cv::Mat::zeros(4, 4, CV_64F);
    R_cam2gripper.copyTo(T_cam2gripper(rotation_rect));
    t_cam2gripper.copyTo(T_cam2gripper(translation_rect));
    std::cout << "Estimated cam2gripper: \n" << T_cam2gripper << '\n';
}