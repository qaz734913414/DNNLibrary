#include <string>
#include <fstream>
#include <numeric>
#include <map>

#include <glog/logging.h>
#include <common/StrKeyMap.h>
#include "OnnxConverter.h"
#include "NodeAttrHelper.h"
#include "common/log_helper.h"

using std::string; using std::vector;


int main(int argc, char **argv) {
    FLAGS_logtostderr = true;
    google::InitGoogleLogging(argv[0]);
    if (argc != 3) {
        std::cerr << "argc must be 3" << std::endl;
        return -1;
    }
    ONNX_NAMESPACE::ModelProto model_proto;
    {
        std::ifstream ifs(argv[1], std::ios::in | std::ios::binary);
        model_proto.ParseFromIstream(&ifs);
        ifs.close();
    }

    OnnxConverter converter;
    converter.Convert(model_proto, argv[2]);

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
