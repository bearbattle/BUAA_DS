int num[12][7] = {
    //标准字库
    {1, 1, 1, 1, 1, 1, 0}, //0 or O
    {0, 1, 1, 0, 0, 0, 0}, //1
    {1, 1, 0, 1, 1, 0, 1}, //2
    {1, 1, 1, 1, 0, 0, 1}, //3
    {0, 1, 1, 0, 0, 1, 1}, //4
    {1, 0, 1, 1, 0, 1, 1}, //5
    {1, 0, 1, 1, 1, 1, 1}, //6
    {1, 1, 1, 0, 0, 0, 0}, //7
    {1, 1, 1, 1, 1, 1, 1}, //8
    {1, 1, 1, 1, 0, 1, 1}, //9
    {1, 0, 0, 0, 1, 1, 1}, //F,10
    {0, 0, 0, 0, 0, 0, 0}  //NULL,11
};

int Cube[3] = {2, 3, 4}; //数码管引脚
int Trig = 12;
int Echo = 13; //超声波测距引脚
int Green = 14;
int Red = 15; //LED引脚

double SonicDis();
void LEDControl(int pin, int val);
void DisplayAns(int ans);
void CubeSelect(int pin);
void DisplayNum(int n);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    for (int i = 2; i <= 15; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    int t = 50;
    double dis = SonicDis();
    Serial.print(dis, 2);
    Serial.println("cm");
    if (dis < 5)
    {
        LEDControl()
    }
    DisplayAns(dis, t);
}

double SonicDis()
{
    double dis;
    // 检测脉冲宽度，并计算出距离
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    dis = pulseIn(Echo, HIGH) / 58.00;
    return dis;
}

void LEDControl(int pin, int t)
{
    while (t--)
    {
    }
    return 1;
}
if (pin > 150)
{
    digitalWrite(15, HIGH);
    while (t--)
    {
        CubeSelect(2);
        DisplayNum(10);
        delay(1);
        DisplayNum(11);
        delay(1);

        CubeSelect(3);
        DisplayNum(10);
        delay(1);
        DisplayNum(11);
        delay(1);

        CubeSelect(4);
        DisplayNum(0);
        delay(1);
        DisplayNum(11);
        delay(1);
    }
    return 1;
}
digitalWrite(14, LOW);
digitalWrite(15, LOW);
return 0;
}

void DisplayNum(int n) //单数字显示
{
    for (int i = 0; i < 7; i++)
        digitalWrite(5 + i, num[n][i]);
}

void DisplayAns(double dis)
{
    int ans;
    while (dis <= 100)
        dis *= 10;
    ans = (int)dis;
    while (t--)
    {
        CubeSelect(2);
        DisplayNum(ans % 10);
        delay(1);
        DisplayNum(11);
        delay(1);

        CubeSelect(3);
        DisplayNum(ans / 10 % 10);
        delay(1);
        DisplayNum(11);
        delay(1);

        CubeSelect(4);
        DisplayNum(ans / 100);
        delay(1);
        DisplayNum(11);
        delay(1);
    }
}

void CubeSelect(int led)
{
    for (int i = 2; i <= 4; i++)
        digitalWrite(i, i == led ? LOW : HIGH);
}