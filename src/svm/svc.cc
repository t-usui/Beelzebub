#include "svc.h"

namespace beelzebub{
	SVC::SVC(){
		printf("Starting up Beelzebub's Support Vector classifier");
		printf("... ");
		this->SetupSvmParameter();

		printf(" Done.\n");

		printf("LibSVM version: %d\n", libsvm_version);
	}


	SVC::~SVC(){
		printf("OK");
	}


	void SVC::SetupTrainingData(){
		printf("Inputting training data... ");

		this->training_data_[0][0].index = 1;
		this->training_data_[0][0].value = 3;
		this->training_data_[0][1].index = -1;
		this->training_data_[1][0].index = 2;
		this->training_data_[1][0].value = 3;
		this->training_data_[1][1].index = -1;
		this->training_data_[2][0].index = 3;
		this->training_data_[2][0].value = 3;
		this->training_data_[2][1].index = -1;

		printf("Done.\n");

		return;
	}


	void SVC::SetupTestData(){
		printf("Inputting test data...");

		this->test_data_[0].index = 1;
		this->test_data_[0].value = 3;
		this->test_data_[1].index = -1;

		printf("Done.\n");

		return;
	}


	void SVC::SetupSvmParameter(){
		this->svm_parameter_.svm_type		= NU_SVC;
		this->svm_parameter_.kernel_type	= RBF;
		this->svm_parameter_.degree		= 2;
		this->svm_parameter_.gamma		= 0.2;
		this->svm_parameter_.coef0		= 1;
		this->svm_parameter_.nu			= 0.2;
		this->svm_parameter_.cache_size		= 100;
		this->svm_parameter_.C			= 100;
		this->svm_parameter_.eps		= 0.00001;
//		this->svm_parameter_.eps		= 1e-3;
		this->svm_parameter_.p			= 0.1;
		this->svm_parameter_.shrinking		= 0.1;
		this->svm_parameter_.probability	= 0;
		this->svm_parameter_.nr_weight		= 0;
		this->svm_parameter_.weight_label	= NULL;

		return;
	}


	void SVC::CheckSvmParameter(){
		std::string ret;

		printf("Checking parameters... ");

		ret = svm_check_parameter(&this->svm_problem_, &this->svm_parameter_);
		if(ret == NULL){
			printf("Done. NO problem.\n");
		}else{
			printf("Error! %s\n", ret);
		}

		return;
	}


	void SVC::BuildSvmProblem(){
		this->svm_problem_.l = this->kSvmProblemNumber;
		this->svm_problem_.y = new double[this->svm_problem_.l];

		for(int i=0;i<this->svm_problem_.l;i++){
			printf("%f\n", this->svm_problem_.y[i]);
			this->svm_problem_.y[i] = i + 1;
		}

		this->svm_problem_.x = new svm_node*[this->svm_problem_.l];
		*this->svm_problem_.x[0] = this->training_data_[0];
		*this->svm_problem_.x[1] = this->training_data_[1];
		*this->svm_problem_.x[2] = this->training_data_[2];

		return;
	}


	void SVC::BuildSvmModel(){
		int class_number;

		printf("Building model... ");

		this->svm_model_ = svm_train(&this->svm_problem_, &this->svm_parameter_);
		class_number =  svm_get_nr_class(this->svm_model_);

		printf("Done. The number of class: %d\n", class_number);

		return;
	}


	double SVC::ClassifyTestData(){
		double result;

		result = svm_predict(svm_model_, test_data_);
		printf("Result of classification: %f\n", result);

		return result;
	}


	void SVC::FinishSvm(){
		return;
	}
}

int main(void){



	printf("finished\n");
/*
	printf("%d\n", (*SvmProblem.x)->index);
	printf("%f\n", (*SvmProblem.x)->value);
	printf("%d\n", ((*SvmProblem.x)+1)->index);
	printf("%f\n", ((*SvmProblem.x)+1)->value);
	printf("%d\n", (*(SvmProblem.x+1))->index);
	printf("%f\n", (*(SvmProblem.x+1))->value);
*/


	exit(EXIT_SUCCESS);
}
