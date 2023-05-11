#include <stdio.h>
#include <stdlib.h>
#include <TH1.h>
#include <TApplication.h>

double square(double num)
{
    return num*num;
}

double integral(double* tau, double* zeta, double* theta)
{
    int i=0;
    double sum=0, subsum;
    
    for(i=0;i<15;i++)
    {
        subsum=(((square((zeta[i+1]-zeta[i])/(tau[i+1]-tau[i]))+square(zeta[i])*square((theta[i+1]-theta[i])/(tau[i+1]-tau[i])))/2+1/zeta[i])*(tau[i+1]-tau[i]));
        sum+=subsum;
    }
    
    return sum;
}



void Saving(char* filename,double* tau1, double* zeta1, double* theta1)
{
	char s1[100],c1[100],c2[100],c3[100];
    int i=0;
    FILE *fp = fopen(filename, "r");
    while (fgets(s1,100,fp)!=NULL)
    {
        sscanf(s1,"%s %lg, %s %lg, %s %lg",c1,tau1+i,c2,zeta1+i,c3,theta1+i);
        printf("%lg, %lg, %lg\n",tau1[i],zeta1[i],theta1[i]);
        i++;
    }
    fclose(fp);
    return;
}

void histogram(double a,double b,double c, double d, double e, double f, double g, double h) {
    TH1D *hist = new TH1D("name", "Actions;;Action", 8, 0, 20);
    hist->GetXaxis()->SetBinLabel(1, "straight");
    hist->GetXaxis()->SetBinLabel(2, "theta first");
    hist->GetXaxis()->SetBinLabel(3, "theta para conv down");
    hist->GetXaxis()->SetBinLabel(4, "theta conv up");
    hist->GetXaxis()->SetBinLabel(5, "zeta first");
    hist->GetXaxis()->SetBinLabel(6, "zeta para conv down");
    hist->GetXaxis()->SetBinLabel(7, "zeta para conv up");
    hist->GetXaxis()->SetBinLabel(8, "best path");
    hist->Fill("straight", a);
    hist->Fill("theta first", b);
    hist->Fill("theta para conv down", c);
    hist->Fill("theta conv up", d);
    hist->Fill("zeta first", e);
    hist->Fill("zeta para conv down", f);
    hist->Fill("zeta para conv up", g);
    hist->Fill("best path", h);
    hist->SetLineWidth(0); // Remove strange line graph
    hist -> Draw("BAR");
    return;
}

double Result(char *filename,double* tau1, double* zeta1, double* theta1)
{    
    Saving(filename,tau1, zeta1,theta1);
    return integral(tau1, zeta1,theta1);
}

int main()
{
    char file1[100]="bestpath.txt";
    double tau1[16],zeta1[16],theta1[16];
    double a,b,c,d,e,f,g,h;
    a=Result("straight",tau1, zeta1,theta1);
    b=Result("theta first",tau1, zeta1,theta1);
    c=Result("theta para conv down",tau1, zeta1,theta1);
    d=Result("theta conv up",tau1, zeta1,theta1);
    e=Result("zeta first",tau1, zeta1,theta1);
    f=Result("zeta para conv down",tau1, zeta1,theta1);
    g=Result("zeta para conv up",tau1, zeta1,theta1);
    h=Result("best path",tau1, zeta1,theta1);
    TApplication theApp("App", 0, 0);
    histogram(a,b,c,d,e,f,g,h);
    theApp.Run();
    return 0;
}