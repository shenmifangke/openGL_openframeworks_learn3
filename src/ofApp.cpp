#include "ofApp.h"
/*
使用内置坐标
http://bullteacher.com/category/zh_learnopengl_com


http://bullteacher.com/7-textures.html
http://learnopengl-cn.readthedocs.org/zh/latest/


http://www.learnopengl.com/#!Code-repository


*/
//下面的库需要另外下 这里旋转之类我们使用of自带的库
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
string  ofApp::loadFragmentShader( string sPath )
{
    ofFile F;
//    F.clear();
//    F.close();
    F.open(ofToDataPath(sPath), ofFile::ReadWrite, false);
    string ccc = F.readToBuffer().getText();
    return ccc;
}


GLuint EBO;//索引缓冲对象 多个三角形必须使用索引 可以减少重复的顶点
GLuint vbo;//顶点缓冲对象
GLuint vao;//顶点数组对象
const char* vertex_shader;
const char* fragment_shader;
GLuint shader_programme;
//core-profile模式 所有新版本的OpenGL都是以3.3为基础
//这里使用的就是glfw3




void ofApp::setup(){

    cam.setDistance(100);
    cam.enableMouseInput();
//开启深度缓冲
glEnable(GL_DEPTH_TEST);


GLint nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);//一般大于等于16
std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

//自带的矩阵
//glm::vec4;
//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);//(1,0,0)的齐次坐标
//glm::mat4 trans;//定义一个默认mat4的4×4单位矩阵
//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
//vec = trans * vec;
//std::cout << vec.x << vec.y << vec.z << std::endl;//210
ofVec3f vec = ofVec3f(1,0,0);
ofMatrix4x4 mat4 = ofMatrix4x4();
mat4.translate(ofVec3f(1,1,0));
vec = vec*mat4;
cout<<vec<<endl;

GLfloat points[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


ofVec3f temp[10] = {
        ofVec3f( 0.0f,  0.0f,  0.0f),
        ofVec3f( 2.0f,  5.0f, -15.0f),
        ofVec3f(-1.5f, -2.2f, -2.5f),
        ofVec3f(-3.8f, -2.0f, -12.3f),
        ofVec3f( 2.4f, -0.4f, -3.5f),
        ofVec3f(-1.7f,  3.0f, -7.5f),
        ofVec3f( 1.3f, -2.0f, -2.5f),
        ofVec3f( 1.5f,  2.0f, -2.5f),
        ofVec3f( 1.5f,  0.2f, -1.5f),
        ofVec3f(-1.3f,  1.0f, -1.5f)
    };
//    for(int i=0;i<10;i++){
//cubePositions[i] = temp[i];
//}
memcpy(cubePositions,temp,10*sizeof(ofVec3f));//效率比上面更高
//----------------------------------------------------vao绑定
glGenVertexArrays (1, &vao);
glGenBuffers (1, &vbo);


glBindVertexArray (vao);

glBindBuffer (GL_ARRAY_BUFFER, vbo);
glBufferData (GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

// 顶点属性
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);//定义OpenGL如何解释顶点数据，我们也要开启顶点属性
// UV属性
glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (GLvoid * )(3*sizeof(GLfloat)));
glEnableVertexAttribArray(2);

glBindVertexArray(0);//解开vao绑定
//----------------------------------------------------vao绑定





string a = loadFragmentShader("fragment.frag");
string b = loadFragmentShader("vertex_shader.vert");


fragment_shader = a.c_str();//必须用string变量进行一次多余操作 否则会有未知原因 可能是执行速度造成未载入
vertex_shader = b.c_str();


GLint success;//是否错误
GLchar infoLog[512];//储存错误消息的容器



//动态编译glsl的源码 创建一个着色器对象，再次引用它的ID。所以我们储存这个顶点着色器为GLuint，然后用glCreateShader创建着色器
GLuint vs = glCreateShader (GL_VERTEX_SHADER);//把着色器的类型提供glCreateShader作为它的参数。这里我们传递的参数是GL_VERTEX_SHADER这样就创建了一个顶点着色器
glShaderSource (vs, 1, &vertex_shader, NULL);//把这个着色器源码附加到着色器对象，然后编译它 第二参数指定了源码中有多少个字符串，这里只有一个。第三个参数是顶点着色器真正的源码
glCompileShader (vs);//这步之后才能进行错误检测
//vs顶点着色器错误检测
glGetShaderiv(vs, GL_COMPILE_STATUS, &success);//用来检测错误
if(!success)
{
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}



GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);//使用GL_FRAGMENT_SHADER作为着色器类型
glShaderSource (fs, 1, &fragment_shader, NULL);
glCompileShader (fs);
//fs片段着色器错误检测
glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(fs, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRANMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
}


//着色器程序对象（shader program object）是多个着色器最后链接的版本。我们必须把它们链接为一个着色器程序对象，当渲染物体激活着色器程序。
//把着色器链接为一个程序就等于把每个着色器的输出链接到下一个着色器的输入。
shader_programme = glCreateProgram ();
glAttachShader (shader_programme, fs);
glAttachShader (shader_programme, vs);
glLinkProgram (shader_programme);

//着色器程序对象附加错误检测
glGetProgramiv(shader_programme, GL_LINK_STATUS, &success);

if(!success) {
    glGetProgramInfoLog(shader_programme, 512, NULL, infoLog);
    std::cout << "last shader program object error \n" << infoLog << std::endl;
}


//最后删除着色器对象
glDeleteShader(vs);
glDeleteShader(fs);
//OpenGL至少提供16个纹理单元供你使用，也就是说你可以激活GL_TEXTURE0到GL_TEXTRUE15。它们都是顺序定义的，所以我们也可以通过GL_TEXTURE0+8的方式获得GL_TEXTURE8，这个例子在当我们不得不循环几个纹理的时候变得很有用。
//////////////////////////////生成绑定纹理 这里没有使用教程中的Simple OpenGL Image Library（简易OpenGL图像库）而是使用了of自带的freeimage库
ofImage image;//使用of自带的转换image.getPixels() 可以转换为const GLvoid*格式
image.loadImage("1.png");//放在data目录里
ofImage image2;
image2.loadImage("2.jpg");

glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);
// Set the texture wrapping/filtering options (on the currently bound texture object)
//纹理放置方式（Texture Wrapping）
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//纹理过滤（Texture Filtering）
//中间项目 纹理过滤可已设置放大和缩小的选项，这样你可以在纹理被缩小的时候使用最临近过滤，被放大时使用线性过滤。我们必须通过glTexParameter*为放大和缩小指定过滤方式。
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// Load and generate the texture
//int width, height;
//unsigned char * image = SOIL_load_image("container.jpg", &width, &eight, 0, SOIL_LOAD_RGB);

//第一个参数指定纹理目标（环境）；设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标（target）上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
//第二个参数为我们打算创建的纹理指定mipmap层级，如果你希望为每个mimap层级单独手工设置的话。这里我们填0基本级。
//第三个参数告诉OpenGL，我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们把纹理储存为RGB值。
//第四个和第五个参数设置最终的纹理的宽度和高度。我们加载图像的时候提前储存它们这样我们就能使用相应变量了。
//第六个参数应该一直被设为0（遗留问题）。
//第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存在char(byte)
//最后一个参数是真实的图像数据。
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixels());//这里改成了RGBA 因为用的是透明png
glGenerateMipmap(GL_TEXTURE_2D);
//SOIL_free_image_data(image);
glBindTexture(GL_TEXTURE_2D, 0);//生成了纹理和相应的mipmap后，解绑纹理对象、释放图像的内存很重要。




glGenTextures(2, &texture2);
glBindTexture(GL_TEXTURE_2D, texture2);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2.width, image2.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2.getPixels());//这里改成了RGB 因为用的是jpg
glGenerateMipmap(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 1);



//ofVec3f cameraPos = ofVec3f(0.0f, 0.0f, 3.0f);//摄像机位置
//ofVec3f cameraTarget = ofVec3f(0.0f, 0.0f, 0.0f);//目标方向
//ofVec3f cameraDirection = ofVec3f.normalize(cameraPos - cameraTarget);//摄像机方向


//Look At 目标摄像机

GLfloat radius = 10.0f;
GLfloat camX = sin(ofGetElapsedTimef()) * radius;
GLfloat camZ = cos(ofGetElapsedTimef()) * radius;
ofMatrix4x4 view = ofMatrix4x4();
//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                     //位置、目标和上向量
//view.getLookAt(ofVec3f(0.0f, 0.0f, 3.0f),
//ofVec3f(0.0f, 0.0f, 0.0f),
//ofVec3f(0.0f, 1.0f, 0.0f));

}

//--------------------------------------------------------------
void ofApp::update(){

}
#include <GLFW/glfw3.h>//glfwGetTime函数需要引入
//--------------------------------------------------------------
void ofApp::draw(){


glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//必须放在draw里 glClearColor函数是一个状态设置函数
//glClear(GL_COLOR_BUFFER_BIT);//glClear是一个状态使用函数
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




  // wipe the drawing surface clear
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram (shader_programme);//// 激活着色器 调用glUseProgram函数，用新创建的程序对象作为它的参数，这样就能激活这个程序对象


   // glBindTexture(GL_TEXTURE_2D, texture1);//绘制的时候需要增加一句绑定纹理

//激活多个纹理
glActiveTexture(GL_TEXTURE0); //在绑定纹理之前，先激活纹理单元 单纹理的时候可以忽略这个单元
glBindTexture(GL_TEXTURE_2D, texture1);
glUniform1i(glGetUniformLocation(shader_programme, "ourTexture1"), 0);//单一纹理的时候可以忽略这个值

glActiveTexture(GL_TEXTURE1); //激活纹理单元2
glBindTexture(GL_TEXTURE_2D, texture2);
glUniform1i(glGetUniformLocation(shader_programme, "ourTexture2"), 1);



        // Create transformations
//        glm::mat4 model;
//        glm::mat4 view;
//        glm::mat4 projection;
//        model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
//        // Get their uniform location
//        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
//        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
//        GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
//        // Pass them to the shaders
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//        // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

ofMatrix4x4 model = ofMatrix4x4();
ofMatrix4x4 view = ofMatrix4x4();
ofMatrix4x4 projection = ofMatrix4x4();
model.rotate(-55.0f,1.0f, 0.0f, 0.0f);
view.translate(0.0f, 0.0f, -3.0f);
projection.makePerspectiveMatrix(45.0f,(float)ofGetWidth()/(float)ofGetHeight(), 0.1f, 100.0f);



        GLint modelLoc = glGetUniformLocation(shader_programme, "model");
        GLint viewLoc = glGetUniformLocation(shader_programme, "view");
        GLint projLoc = glGetUniformLocation(shader_programme, "projection");
//        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.getPtr());
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.getPtr());
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.getPtr());

//转入矩阵
//GLuint transformLoc = glGetUniformLocation(shader_programme, "transform");
//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat4.getPtr());





  glBindVertexArray (vao);



//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao);//用GL_ELEMENT_ARRAY_BUFFER当作缓冲目标  不同于上面一种绘制方式
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) 线模式

  //第一个参数指定了我们绘制的模式，这个和glDrawArrays的一样
  //第二个参数是我们打算绘制顶点的次数。我们填6，说明我们总共想绘制6个顶点。
  //第三个参数是索引的类型，这里是GL_UNSIGNED_INT。
  //最后一个参数里我们可以指定EBO中的偏移量（或者传递一个索引数组，但是这只是当你不是在使用索引缓冲对象的时候），但是我们只打算在这里填写0
  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//用glDrawElements来替换glDrawArray 来指明我们从索引缓冲渲染


        for (GLuint i = 0; i < 10; i++)
        {
//            glm::mat4 model;
            ofMatrix4x4 model;
//            model = glm::translate(model, cubePositions[i]);
            model.translate(cubePositions[i]);
            GLfloat angle = 1.0f * (i+1);
//            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            model.rotate(angle*ofGetElapsedTimef(),1.0f, 0.3f, 0.5f);
//            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.getPtr());

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


  glBindVertexArray(0);//解开vao绑定

//cam.begin();
//    ofPushStyle();
//	ofSetColor(255,0,0);
//	ofFill();
//	ofDrawBox(30);
//	ofNoFill();
//	ofSetColor(0);
//	ofDrawBox(30);
//
//	ofPushMatrix();
//	ofTranslate(0,0,20);
//	ofSetColor(0,0,255);
//	ofFill();
//	ofDrawBox(5);
//	ofNoFill();
//	ofSetColor(0);
//	ofDrawBox(5);
//	ofPopMatrix();
//	ofPopStyle();
//  cam.end();
}
void ofApp::exit()
{
    cout<<"exit"<<endl;
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
