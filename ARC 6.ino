int Position;


#define right_pos  5
#define right_neg  4
#define right_enb  6

#define left_pos  8
#define left_neg  7
#define left_enb  9

#define trig_R 2
#define echo_R A0
#define trig_L 3
#define echo_L A1
#define trig_F 12
#define echo_F A2
int distance_r = 0 , distance_l = 0 , distance_m = 0 , t = 0;

#define shoterp   10
#define shotern   13
char coming_value='0';


char maze_type='0';
int after_maze=0;

void setup() {
  //  setup code :
  Serial.begin(9600);
pinMode(right_pos,OUTPUT);
pinMode(right_neg,OUTPUT);
pinMode(right_enb,OUTPUT);
pinMode(left_pos,OUTPUT);
pinMode(left_neg,OUTPUT);
pinMode(left_enb,OUTPUT);
pinMode(shoterp,OUTPUT);
pinMode(shotern,OUTPUT);
myservo.attach(11);
pinMode(trig_R,OUTPUT);
pinMode(echo_R,INPUT);
pinMode(trig_L,OUTPUT);
pinMode(echo_L,INPUT);
pinMode(trig_F,OUTPUT);
pinMode(echo_F,INPUT);
}

void loop() {
  //  main code :
   

 if (Serial.available()>0)
    coming_value=Serial.read();
   
  
    if(coming_value=='A'){
      
       digitalWrite(trig_R,LOW);
 delayMicroseconds(5);
 digitalWrite(trig_R,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig_R,LOW); 
 t=pulseIn(echo_R,HIGH);
 distance_r = t/57;
 
 digitalWrite(trig_L,LOW);
 delayMicroseconds(5);
 digitalWrite(trig_L,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig_L,LOW); 
 t=pulseIn(echo_L,HIGH);
 distance_l = t/57;
 digitalWrite(trig_F,LOW);
 delayMicroseconds(5);
 digitalWrite(trig_F,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig_F,LOW); 
 t=pulseIn(echo_F,HIGH);
 distance_m = t/57;
 Serial.println(distance_m );
 Serial.println("   " );
 Serial.println(distance_r );
 Serial.println("   " );
 Serial.println(distance_l );
  Serial.println("\n");
  if(Position==0){
    forward();
    delay(1000);
     stop_moving();
    Position+1;
  }
  if(after_maze==0){
  if(distance_m>30){
      forward();
  
   //   if(distance_r<16&&distance_l<16)
       // correcting_direction();
  }
      else if(distance_r>=16&&distance_l<16){
      turn_right;
       if(maze_type=='0')maze_type='r';}
      else if(distance_r<=16&&distance_l>16){
       turn_left;
       if(maze_type=='0')maze_type='l';
       }
     else if(distance_m>30&&distance_r>20&&distance_l>20){
     after_maze=1;
        
       }
        }
    else if(after_maze==1){
      
    while(distance_r>70 && maze_type=='l')forward();
    while(distance_l>70 && maze_type=='r')forward();
    delay(5000);
     after_maze=2;
      while (distance_m>90)
     forward();

    shot();
    }
    } 
    else{
      maze_type='0';
      after_maze=0;
       if(coming_value=='1')
    forward();
    else if (coming_value=='2')
    rearward();
    else if (coming_value=='3')
    turn_rightw();
    else if (coming_value=='4')
    turn_leftw();
    else if (coming_value=='5')
    spin_right();
    else if (coming_value=='6')
    spin_left();
    else if (coming_value=='7')
    turn_right();
    else if (coming_value=='8')
    turn_left();
    else if (coming_value=='9')
    shot();
    else if(coming_value=='0')
    stop_moving();
     else if(coming_value=='s')
    stop_shot();
    
    
    
    }
    
  }
  void forward(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,200);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,200);
  } 
  void rearward(){
  digitalWrite(right_pos,0);
  digitalWrite(right_neg,1);
  analogWrite(right_enb,200);
  digitalWrite(left_pos,0);
  digitalWrite(left_neg,1);
  analogWrite(left_enb,200);
  } 
  void turn_left(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,150);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,0);
  } 
  void turn_right(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,0);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,150);}
   void turn_leftw(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,200);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,125);
  } 
  void turn_rightw(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,75);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,200);}
   void spin_left(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,200);
  digitalWrite(left_pos,0);
  digitalWrite(left_neg,1);
  analogWrite(left_enb,200);}
  void spin_right(){
  digitalWrite(right_pos,0);
  digitalWrite(right_neg,1);
  analogWrite(right_enb,200);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,200);}
  void stop_moving(){
  digitalWrite(right_pos,0);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,200);
  digitalWrite(left_pos,0);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,200);}
 void shot(){
    digitalWrite(shoterp,1);
    digitalWrite(shotern,0);
  }
   inline void stop_shot(){
  digitalWrite(shoterp,0);}
   void shot_left(){
  digitalWrite(right_pos,1);
  digitalWrite(right_neg,0);
  analogWrite(right_enb,125);
  digitalWrite(left_pos,0);
  digitalWrite(left_neg,1);
  analogWrite(left_enb,125);}
   void shot_right(){
  digitalWrite(right_pos,0);
  digitalWrite(right_neg,1);
  analogWrite(right_enb,125);
  digitalWrite(left_pos,1);
  digitalWrite(left_neg,0);
  analogWrite(left_enb,125);}
  
 

 
  void correcting_direction(){
 if (distance_r-distance_l>4){
      turn_right();
      delay(1000);
      forward();
      delay(1000);
      turn_left();
      delay(1000);
      }
      if (distance_l-distance_r>4){
      turn_left();
      delay(1000);
      forward();
      delay(1000);
      turn_right();
      delay(1000);
      }
  }
