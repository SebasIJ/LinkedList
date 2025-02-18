#include "ofApp.h"

//Sebastian Igua Jimenez 2410370
//Using lecture notes as reference

//every circle has a radius, a x and y position and a boolean that determines what direction its going
struct circle {
    int radius;
    int x;
    int y;
    bool goUp = true;
    circle(int r, int x, int y) : radius(r), x(x), y(y) {}
};

//linked list node that contains a circle and a pointer to the next node
struct circleNode {
    circle data;
    circleNode* next;
    circleNode(int r, int x, int y) : data(r,x,y), next(nullptr) {}
};

//class containing the methods necessary to modify the linked list
class LinkedList
{
public:

    //initial head
    circleNode* head;


    void insertAtHead(int newR, int newX, int newY) {

        //creates a new node, sets the old head node as its next pointer and sets it as the new head
        circleNode* newNode = new circleNode(newR, newX, newY);
        newNode->next = head;
        head = newNode;

    }

    void insertAtTail(int newR, int newX, int newY) {

        //creates a new node
        circleNode* newNode = new circleNode(newR, newX, newY);        

        //sets a temporary node to go through the list
        circleNode* temp = head;

        //goes through the list until the final node
        while (temp->next)
        {
            temp = temp->next;
        }
        //puts the new node at the end of the list
        temp->next = newNode;

    }

    void deleteHead() {

        //gets the head node, sets the next node as the new head and deletes the old head
        circleNode* temp = head;
        head = head->next;
        delete temp;

    }

    void deleteTail() {

        //temporary node
        circleNode* temp = head;

        //goes through the list until the second to last
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }

        //deletes the next node being the last one
        delete temp->next;
        //removes the pointer in the new last node
        temp->next = nullptr;

    }

};

//linked list to be used in the visuals
LinkedList thisList;
//minimum and maximum y positions for the animation
int minY = 200;
int maxY = 400;

//--------------------------------------------------------------
void ofApp::setup(){

    //generates a random number from 10 to 50
    int value = rand() % (40 + 1);
    value += 10;
    //sets the head node with the random value as the radius
    thisList.head = new circleNode(value, 500, minY);

}

//--------------------------------------------------------------
void ofApp::update(){

    //note: using ofGetLastFrameTime can cause the circles to desync from the animation pattern

    //gets the head node
    circleNode* temp = thisList.head;

    //goes through the list
    while (temp->next)
    {
        //checks what direction the current circle is going in
        if (temp->data.goUp) {

            //animates the circle by changing the y position
            temp->data.y += 2;

            //checks if the circle should change direction and changes it if necessary
            if (temp->data.y >= maxY) {
                temp->data.goUp = false;
            }

        }
        else {

            //animates the circle by changing the y position
            temp->data.y -= 2;

            //checks if the circle should change direction and changes it if necessary
            if (temp->data.y <= minY) {
                temp->data.goUp = true;
            }

        }
        //goes to the next node
        temp = temp->next;
    }

    //does the same animation logic out of the loop once
    //tail node does not get animated otherwise
    if (temp->data.goUp) {

        temp->data.y += 2;

        if (temp->data.y >= maxY) {
            temp->data.goUp = false;
        }

    }
    else {

        temp->data.y -= 2;

        if (temp->data.y <= minY) {
            temp->data.goUp = true;
        }

    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    //gets head node
    circleNode* temp = thisList.head;
    //goes through the list
    while (temp->next)
    {
        //sets draw color to white
        ofSetColor(255, 255, 255);
        //draws a circle with the current node information
        ofDrawCircle(temp->data.x, temp->data.y, temp->data.radius);

        //draws a line to from the current node to the next
        if (temp->next != nullptr) {

            ofDrawLine(temp->data.x, temp->data.y, temp->next->data.x, temp->next->data.y);

        }

        //sets draw color to black
        ofSetColor(0, 0, 0);
        //writes the radius on top of the circle
        ofDrawBitmapString(temp->data.radius, temp->data.x - 10, temp->data.y + 5);
        //goes to the next node
        temp = temp->next;
    }

    //draws the tail node outside of the loop
    ofSetColor(255, 255, 255);
    ofDrawCircle(temp->data.x, temp->data.y, temp->data.radius);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(temp->data.radius, temp->data.x - 10, temp->data.y + 5);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    //needed variables have to be initialized outside of the switch case otherwise it does not work
    int value = rand() % (40 + 1); //random value to use as radius when making a new node
    value += 10;
    int Ydiff = 0; //vertical separation between circles when resetting positions
    circleNode* temp = thisList.head; //gets head node

    switch (key)
    {
    case 'Q':
    case 'q':

        //inserts a new head node
        thisList.insertAtHead(value, thisList.head->data.x - 100, minY);

        //goes through the list setting default y positions so the animation lines up with the added node
        Ydiff = 0;

        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.y = minY + Ydiff;
            temp->data.goUp = true;
            Ydiff += 10;
            temp = temp->next;
        }

        temp->data.y = minY + Ydiff;
        temp->data.goUp = true;

        break;

    case 'W':
    case 'w':
        
        //gets the current tail node to get its x position
        temp = thisList.head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        //inserts a new tail node
        thisList.insertAtTail(value, temp->data.x + 100, minY);

        //goes through the list setting default y positions so the animation lines up with the added node
        Ydiff = 0;

        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.y = minY + Ydiff;
            temp->data.goUp = true;
            Ydiff += 10;
            temp = temp->next;
        }

        temp->data.y = minY + Ydiff;
        temp->data.goUp = true;

        break;

    case 'A':
    case 'a':

        //deletes head node
        thisList.deleteHead();

        break;

    case 'S':
    case 's':

        //deletes tail node
        thisList.deleteTail();

        break;

    case 'Z':
    case 'z':

        //increases maximum y to increase amplitude
        maxY+=10;

        //goes through the list setting default y positions so the animation lines up with the new amplitude
        Ydiff = 0;

        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.y = minY + Ydiff;
            temp->data.goUp = true;
            Ydiff += 10;
            temp = temp->next;
        }

        temp->data.y = minY + Ydiff;
        temp->data.goUp = true;

        break;

    case 'X':
    case 'x':

        //decreases maximum y to decrease amplitude
        //maximum cannot be lower than minimum
        if (maxY > minY) {
            maxY-=10;
        }

        //goes through the list setting default y positions so the animation lines up with the new amplitude
        Ydiff = 0;

        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.y = minY + Ydiff;
            temp->data.goUp = true;
            Ydiff += 10;
            temp = temp->next;
        }

        temp->data.y = minY + Ydiff;
        temp->data.goUp = true;

        break;

    case 'c':
    case'C':

        //moves all the circles horizontally to simulate the view scrolling
        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.x += 5;
            temp = temp->next;
        }

        temp->data.x += 5;

        break;

    case 'v':
    case 'V':

        //moves all the circles horizontally to simulate the view scrolling
        temp = thisList.head;

        while (temp->next != nullptr)
        {
            temp->data.x -= 5;
            temp = temp->next;
        }

        temp->data.x -= 5;

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
