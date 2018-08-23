#include "onnUdpd.h"

onnUdpd::onnUdpd():onnObject("onnUdpd"){

}
void onnUdpd::onStart(){
    std::cout << "onnUdpd start" << std::endl;
    flagStart = true;
    emit doStartFinish();
}
