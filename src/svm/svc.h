#ifndef __SVC_H__
#define __SVC_H__

#include "svm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>

namespace beelzebub{
	class SVC{
		private:

		public:
			static const int kSvmProblemNumber = 3;

			svm_problem svm_problem_;
			svm_parameter svm_parameter_;
			svm_model *svm_model_;
			struct svm_node training_data_;
			struct svm_node test_data_;

			SVC();
			~SVC();

			void SetupTrainingData();
			void SetupTestData();
			void SetupSvmParameter();
			void CheckSvmParameter();
			void BuildSvmProblem();
			void BuildSvmModel();
			double ClassifyTestData();
			void FinishSvm();
	};
}

#endif /* __SVC_H__ */
