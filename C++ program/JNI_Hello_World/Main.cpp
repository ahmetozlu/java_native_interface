/*
------------------------------------------------------------------------------------------------------------------------------------
--- Author                          : Ahmet Özlü
--- Mail                            : ahmetozlu93@gmail.com
--- Date                            : 1st August 2017
--- Load .jar file in c++ using JNI : https://stackoverflow.com/questions/40911447/load-jar-file-in-c-using-jni/40913691#40913691
------------------------------------------------------------------------------------------------------------------------------------
*/

#include <jni.h>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	using namespace std;
	JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
	JNIEnv *env;                      // Pointer to native interface
    
	//================== prepare loading of Java VM ============================
	JavaVMInitArgs vm_args;                        // Initialization arguments
	JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
	options[0].optionString = "-Djava.class.path=java_bin";   // where to find java .class
	vm_args.version = JNI_VERSION_1_6;             // minimum Java version
	vm_args.nOptions = 1;                          // number of options
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
    
	//=============== load and initialize Java VM and JNI interface =============
	jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
	delete options;    // we then no longer need the initialisation options. 
	if (rc != JNI_OK) {
		// TO DO: error processing... 
		cin.get();
		exit(EXIT_FAILURE);
	}
    
	//=============== Display JVM version =======================================
	cout << "JVM load succeeded: Version ";
	jint ver = env->GetVersion();
	cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

	jclass cls2 = env->FindClass("Main");  // try to find the class
	
    if (cls2 == nullptr) {
		cerr << "ERROR: class not found !";
	}
    
	else {                                  // if class found, continue
		
        cout << "Class MyTest found" << endl;
		jmethodID mid = env->GetStaticMethodID(cls2, "mymain", "()V");  // find method
		
        if (mid == nullptr)
			cerr << "ERROR: method void mymain() not found !" << endl;
        
		else {
			env->CallStaticVoidMethod(cls2, mid);                      // call method
			cout << endl;
		}

		jvm->DestroyJavaVM();
		cin.get();

	}
}