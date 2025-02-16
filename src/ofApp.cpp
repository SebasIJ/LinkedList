#include "ofApp.h"

//Sebastian Igua Jimenez 2410370
//Using lecture notes as reference

struct circle {
    int radius;
    int x;
    int y;
    bool goUp = true;
    circle(int r, int x, int y) : radius(r), x(x), y(y) {}
};


struct circleNode {
    circle data;
    circleNode* next;
    circleNode(int r, int x, int y) : data(r,x,y), next(nullptr) {}
};

class LinkedList
{
public:

    circleNode* head;


    void insertAtHead(int newR, int newX, int newY) {

        circleNode* newNode = new circleNode(newR, newX, newY);
        newNode->next = head;
        head = newNode;

    }

    void insertAtTail(int newR, int newX, int newY) {

        circleNode* newNode = new circleNode(newR, newX, newY);
        
        if (!head) {

            head = newNode;
            return;

        }

        circleNode* temp = head;

        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;

    }

    void deleteHead() {

        if (!head) return;

        circleNode* temp = head;
        head = head->next;
        delete temp;

    }

    void deleteTail() {

        circleNode* temp = head;

        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }

        delete temp->next;

        temp->next = nullptr;

    }

};

LinkedList thisList;
int minY = 500;
int maxY = 550;

//--------------------------------------------------------------
void ofApp::setup(){

    int value = rand() % (40 + 1);
    value += 10;
    thisList.head = new circleNode(value, 500, minY);

}

//--------------------------------------------------------------
void ofApp::update(){

    //ofGetLastFrameTime()

}

//--------------------------------------------------------------
void ofApp::draw(){

    circleNode* temp = thisList.head;

    while (temp->next)
    {
        ofDrawCircle(temp->data.x, temp->data.y, temp->data.radius);

        temp = temp->next;
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    int value = rand() % (40 + 1);
    value += 10;

    circleNode* temp = thisList.head;

    

    switch (key)
    {
    case 'Q':
    case 'q':

        thisList.insertAtHead(value, thisList.head->data.x - 100, thisList.head->data.y - 5);

        break;

    case 'W':
    case 'w':

        temp = thisList.head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        
        thisList.insertAtTail(value, temp->data.x + 100, temp->data.y + 5);

        break;

    case 'A':
    case 'a':

        thisList.deleteHead();

        break;

    case 'S':
    case 's':

        thisList.deleteTail();

        break;

    case 'Z':
    case 'z':
        break;

    case 'X':
    case 'x':
        break;

    case 'c':

        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.x += 5;
            temp = temp->next;
        }

        break;

    case 'v':

        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.x -= 5;
            temp = temp->next;
        }

        break;

    default:
        break;
    }

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
