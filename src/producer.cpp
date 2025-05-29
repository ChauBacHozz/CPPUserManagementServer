#include <stdexcept>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "cppkafka/producer.h"
#include "cppkafka/configuration.h"

using std::string;
using std::exception;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

using cppkafka::Producer;
using cppkafka::Configuration;
using cppkafka::Topic;
using cppkafka::MessageBuilder;

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
    string brokers;
    string topic_name;
    int partition_value = -1;
    po::options_description options("Options");
    options.add_options()
    ("help,h",      "produce this help message")
    ("brokers,b",   po::value<string>(&brokers)->required(), 
                    "the kafka broker list")
    ("topic,t",     po::value<string>(&topic_name)->required(),
                    "the topic in which to write to")
    ("partition,p", po::value<int>(&partition_value),
                    "the partition to write into (unassigned if not provided)")
    ;

    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(options).run(), vm);
        po::notify(vm);
    }
    catch (exception& ex) {
        cout << "Error parsing options: " << ex.what() << endl;
        cout << endl;
        cout << options << endl;
        return 1;
    }

    MessageBuilder builder(topic_name);


    if (partition_value != -1) {
        builder.partition(partition_value);
    }

    Configuration config = {
        { "metadata.broker.list", brokers }
    };

    Producer producer(config);
    cout << "Producing messages into topic " << topic_name << endl;

    string line;
    while (getline(cin, line))
    {
        builder.payload(line);
        producer.produce(builder);
    }
    producer.flush();
    return 0;
}