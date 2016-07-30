#include "ofApp.h"
/*
ʹ����������
http://bullteacher.com/category/zh_learnopengl_com


http://bullteacher.com/7-textures.html
http://learnopengl-cn.readthedocs.org/zh/latest/


http://www.learnopengl.com/#!Code-repository


*/
//����Ŀ���Ҫ������ ������ת֮������ʹ��of�Դ��Ŀ�
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


GLuint EBO;//����������� ��������α���ʹ������ ���Լ����ظ��Ķ���
GLuint vbo;//���㻺�����
GLuint vao;//�����������
const char* vertex_shader;
const char* fragment_shader;
GLuint shader_programme;
//core-profileģʽ �����°汾��OpenGL������3.3Ϊ����
//����ʹ�õľ���glfw3




void ofApp::setup(){

    cam.setDistance(100);
    cam.enableMouseInput();
//������Ȼ���
glEnable(GL_DEPTH_TEST);


GLint nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);//һ����ڵ���16
std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

//�Դ��ľ���
//glm::vec4;
//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);//(1,0,0)���������
//glm::mat4 trans;//����һ��Ĭ��mat4��4��4��λ����
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
memcpy(cubePositions,temp,10*sizeof(ofVec3f));//Ч�ʱ��������
//----------------------------------------------------vao��
glGenVertexArrays (1, &vao);
glGenBuffers (1, &vbo);


glBindVertexArray (vao);

glBindBuffer (GL_ARRAY_BUFFER, vbo);
glBufferData (GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

// ��������
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);//����OpenGL��ν��Ͷ������ݣ�����ҲҪ������������
// UV����
glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (GLvoid * )(3*sizeof(GLfloat)));
glEnableVertexAttribArray(2);

glBindVertexArray(0);//�⿪vao��
//----------------------------------------------------vao��





string a = loadFragmentShader("fragment.frag");
string b = loadFragmentShader("vertex_shader.vert");


fragment_shader = a.c_str();//������string��������һ�ζ������ �������δ֪ԭ�� ������ִ���ٶ����δ����
vertex_shader = b.c_str();


GLint success;//�Ƿ����
GLchar infoLog[512];//���������Ϣ������



//��̬����glsl��Դ�� ����һ����ɫ�������ٴ���������ID���������Ǵ������������ɫ��ΪGLuint��Ȼ����glCreateShader������ɫ��
GLuint vs = glCreateShader (GL_VERTEX_SHADER);//����ɫ���������ṩglCreateShader��Ϊ���Ĳ������������Ǵ��ݵĲ�����GL_VERTEX_SHADER�����ʹ�����һ��������ɫ��
glShaderSource (vs, 1, &vertex_shader, NULL);//�������ɫ��Դ�븽�ӵ���ɫ������Ȼ������� �ڶ�����ָ����Դ�����ж��ٸ��ַ���������ֻ��һ���������������Ƕ�����ɫ��������Դ��
glCompileShader (vs);//�ⲽ֮����ܽ��д�����
//vs������ɫ��������
glGetShaderiv(vs, GL_COMPILE_STATUS, &success);//����������
if(!success)
{
    glGetShaderInfoLog(vs, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}



GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);//ʹ��GL_FRAGMENT_SHADER��Ϊ��ɫ������
glShaderSource (fs, 1, &fragment_shader, NULL);
glCompileShader (fs);
//fsƬ����ɫ��������
glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(fs, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRANMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
}


//��ɫ���������shader program object���Ƕ����ɫ��������ӵİ汾�����Ǳ������������Ϊһ����ɫ��������󣬵���Ⱦ���弤����ɫ������
//����ɫ������Ϊһ������͵��ڰ�ÿ����ɫ����������ӵ���һ����ɫ�������롣
shader_programme = glCreateProgram ();
glAttachShader (shader_programme, fs);
glAttachShader (shader_programme, vs);
glLinkProgram (shader_programme);

//��ɫ��������󸽼Ӵ�����
glGetProgramiv(shader_programme, GL_LINK_STATUS, &success);

if(!success) {
    glGetProgramInfoLog(shader_programme, 512, NULL, infoLog);
    std::cout << "last shader program object error \n" << infoLog << std::endl;
}


//���ɾ����ɫ������
glDeleteShader(vs);
glDeleteShader(fs);
//OpenGL�����ṩ16������Ԫ����ʹ�ã�Ҳ����˵����Լ���GL_TEXTURE0��GL_TEXTRUE15�����Ƕ���˳����ģ���������Ҳ����ͨ��GL_TEXTURE0+8�ķ�ʽ���GL_TEXTURE8����������ڵ����ǲ��ò�ѭ�����������ʱ���ú����á�
//////////////////////////////���ɰ����� ����û��ʹ�ý̳��е�Simple OpenGL Image Library������OpenGLͼ��⣩����ʹ����of�Դ���freeimage��
ofImage image;//ʹ��of�Դ���ת��image.getPixels() ����ת��Ϊconst GLvoid*��ʽ
image.loadImage("1.png");//����dataĿ¼��
ofImage image2;
image2.loadImage("2.jpg");

glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);
// Set the texture wrapping/filtering options (on the currently bound texture object)
//������÷�ʽ��Texture Wrapping��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//������ˣ�Texture Filtering��
//�м���Ŀ ������˿������÷Ŵ����С��ѡ������������������С��ʱ��ʹ�����ٽ����ˣ����Ŵ�ʱʹ�����Թ��ˡ����Ǳ���ͨ��glTexParameter*Ϊ�Ŵ����Сָ�����˷�ʽ��
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// Load and generate the texture
//int width, height;
//unsigned char * image = SOIL_load_image("container.jpg", &width, &eight, 0, SOIL_LOAD_RGB);

//��һ������ָ������Ŀ�꣨������������ΪGL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ�꣨target���ϵ������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ�죩��
//�ڶ�������Ϊ���Ǵ��㴴��������ָ��mipmap�㼶�������ϣ��Ϊÿ��mimap�㼶�����ֹ����õĻ�������������0��������
//��������������OpenGL������ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ��������ǰ�������ΪRGBֵ��
//���ĸ��͵���������������յ�����Ŀ�Ⱥ͸߶ȡ����Ǽ���ͼ���ʱ����ǰ���������������Ǿ���ʹ����Ӧ�����ˡ�
//����������Ӧ��һֱ����Ϊ0���������⣩��
//���ߵڰ˸�����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ�����char(byte)
//���һ����������ʵ��ͼ�����ݡ�
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixels());//����ĳ���RGBA ��Ϊ�õ���͸��png
glGenerateMipmap(GL_TEXTURE_2D);
//SOIL_free_image_data(image);
glBindTexture(GL_TEXTURE_2D, 0);//�������������Ӧ��mipmap�󣬽����������ͷ�ͼ����ڴ����Ҫ��




glGenTextures(2, &texture2);
glBindTexture(GL_TEXTURE_2D, texture2);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2.width, image2.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2.getPixels());//����ĳ���RGB ��Ϊ�õ���jpg
glGenerateMipmap(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, 1);



//ofVec3f cameraPos = ofVec3f(0.0f, 0.0f, 3.0f);//�����λ��
//ofVec3f cameraTarget = ofVec3f(0.0f, 0.0f, 0.0f);//Ŀ�귽��
//ofVec3f cameraDirection = ofVec3f.normalize(cameraPos - cameraTarget);//���������


//Look At Ŀ�������

GLfloat radius = 10.0f;
GLfloat camX = sin(ofGetElapsedTimef()) * radius;
GLfloat camZ = cos(ofGetElapsedTimef()) * radius;
ofMatrix4x4 view = ofMatrix4x4();
//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                     //λ�á�Ŀ���������
//view.getLookAt(ofVec3f(0.0f, 0.0f, 3.0f),
//ofVec3f(0.0f, 0.0f, 0.0f),
//ofVec3f(0.0f, 1.0f, 0.0f));

}

//--------------------------------------------------------------
void ofApp::update(){

}
#include <GLFW/glfw3.h>//glfwGetTime������Ҫ����
//--------------------------------------------------------------
void ofApp::draw(){


glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�������draw�� glClearColor������һ��״̬���ú���
//glClear(GL_COLOR_BUFFER_BIT);//glClear��һ��״̬ʹ�ú���
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




  // wipe the drawing surface clear
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram (shader_programme);//// ������ɫ�� ����glUseProgram���������´����ĳ��������Ϊ���Ĳ������������ܼ�������������


   // glBindTexture(GL_TEXTURE_2D, texture1);//���Ƶ�ʱ����Ҫ����һ�������

//����������
glActiveTexture(GL_TEXTURE0); //�ڰ�����֮ǰ���ȼ�������Ԫ �������ʱ����Ժ��������Ԫ
glBindTexture(GL_TEXTURE_2D, texture1);
glUniform1i(glGetUniformLocation(shader_programme, "ourTexture1"), 0);//��һ�����ʱ����Ժ������ֵ

glActiveTexture(GL_TEXTURE1); //��������Ԫ2
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

//ת�����
//GLuint transformLoc = glGetUniformLocation(shader_programme, "transform");
//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat4.getPtr());





  glBindVertexArray (vao);



//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao);//��GL_ELEMENT_ARRAY_BUFFER��������Ŀ��  ��ͬ������һ�ֻ��Ʒ�ʽ
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ��ģʽ

  //��һ������ָ�������ǻ��Ƶ�ģʽ�������glDrawArrays��һ��
  //�ڶ������������Ǵ�����ƶ���Ĵ�����������6��˵�������ܹ������6�����㡣
  //���������������������ͣ�������GL_UNSIGNED_INT��
  //���һ�����������ǿ���ָ��EBO�е�ƫ���������ߴ���һ���������飬������ֻ�ǵ��㲻����ʹ��������������ʱ�򣩣���������ֻ������������д0
  //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//��glDrawElements���滻glDrawArray ��ָ�����Ǵ�����������Ⱦ


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


  glBindVertexArray(0);//�⿪vao��

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
