#ifndef BEELZEBUB_DATABASE_H_
#define BEELZEBUB_DATABASE_H_

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <mysql55/mysql/mysql.h>

namespace beelzebub{

class Database{
 private:
  MYSQL *con;
  static const char *kImageDirectory;

 public:
  Database();
  ~Database();

  void ConnectDatabase();
  void CloseDatabase();
  void UpdateDatabase();
  void ExecuteInsertQuery(int id, cv::Mat descriptor);
  int ExecuteSelectQuery(int id, float **feature);
  cv::Mat *LoadOnMemory();

  cv::Mat *descriptors;
  cv::SiftFeatureDetector detector_;
  cv::SiftDescriptorExtractor extractor_;
};

}  // namespace beelzebub

#endif /* BEELZEBUB_DATABASE_H_ */
