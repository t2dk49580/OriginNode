#include "onnChecker.h"

onnChecker::onnChecker():onnObject("onnChecker"){

}
void onnChecker::onStart(){
    std::cout << "onnChecker start" << std::endl;
    flagStart = true;
    emit doStartFinish();
}
