
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int* findHole(int**,int,int);
int* findpath(int,int,int**,int);
int* find(int,int,int**,int,int*,int*,int);
void ksc1p0e(int**,int,int,int);

int flag=0;
char *op;

void main(int argc,char *argv[])
{
  int **M,m,n,i,j,l,k;
  FILE *fp,*fp1;
  op=(char*)malloc(20*sizeof(char));
  strcpy(op,argv[1]);
  strcat(op,"output");

  fp=fopen(argv[1],"r");
  fscanf(fp,"%d",&k);
  fscanf(fp,"%d",&m);
  fscanf(fp,"%d",&n);
  M=(int**)malloc(m*sizeof(int*));//Input Matrix
  
  
  

  for(i=0;i<m;i++)
  { M[i]=(int*)malloc(n*sizeof(int));
  }


  //Constructing Input Matrix from the input file
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
    { fscanf(fp,"%d",&M[i][j]);
    }
  }
  
 
// Calling the function ksc1p0e
 ksc1p0e(M,m,n,k);

fp1=fopen(op,"w");
if(flag==1)
 fprintf(fp1,"YES INSTANCE\n");
else
 fprintf(fp1,"NO INSTANCE\n");

fclose(fp1);

}


void ksc1p0e(int **M,int m, int n,int k)
{  if(k<0) return;

  int **M1,i,j,flag1,flag2,temp,m1,n1,i1,i2,i3,i4,i5,i6,*r,*c,ri,ci;
  char *op;
  int *freqc,*freqr,l;
 
  freqr=(int*)malloc(m*sizeof(int));
  freqc=(int*)malloc(n*sizeof(int));

 for(i=0;i<m;i++)
   freqr[i]=1;
  for(j=0;j<n;j++)
   freqc[j]=1;

  //Preprocessing the input matrix
  
  
//Finding frequency of each row
  for(i=0;i<m;i++)
  { for(j=i+1;j<m;j++)
   { if(freqr[j]!=-1)
     {  for(l=0;l<n;l++)
       { if(M[i][l]!=M[j][l])
           break;
       }
      if(l==n)
       { freqr[i]++;
         freqr[j]=-1;
       }
     }
   }
  }

//Finding frequency of each column
 for(i=0;i<n;i++)
  { for(j=i+1;j<n;j++)
   { if(freqc[j]!=-1)
     {  for(l=0;l<m;l++)
       { if(M[l][i]!=M[l][j])
           break;
       }
      if(l==m)
       { freqc[i]++;
         freqc[j]=-1;
       }
     }
   }
  }

 for(i=0;i<m;i++)
 { if(freqr[i]==-1)
   { for(j=0;j<n;j++)
     { M[i][j]=0;
     }
   }
 }

 for(i=0;i<n;i++)
 { if(freqc[i]==-1)
   { for(j=0;j<m;j++)
     { M[j][i]=0;
     }
   }
 }

  

//Checking for the forbidden submatrix M31 Transpose
  int M31T[4][3]={1,0,0,1,1,1,0,1,0,0,0,1};
  m1=4;
  n1=3;
  
  M1=(int**)malloc(m*sizeof(int*));
  
  r=(int*)malloc(6*sizeof(int));
  c=(int*)malloc(6*sizeof(int));
  c[0]=c[1]=c[2]=-1;
  r[0]=r[1]=r[2]=r[3]=-1;
  ri=0;
  ci=0;

  for(i=0;i<m;i++)
   M1[i]=(int*)malloc(n*sizeof(int));


flag1=0;
for(i1=0;i1<n;i1++)
{ for(i2=0;i2<n;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<n;i3++) //Considering submatrix of columns with indices i1,i2,i3 
    { if(i1==i3) continue;
      if(i2==i3) continue;
      ri=0;ci=0;
      for(i=0;i<m1;i++)
      { for(j=0;j<m;j++)//Checking whether all the rows of M31 are present in the sumatrix induced by columns with indices i1,i2,i3
        { if(M[j][i1]==M31T[i][0] && M[j][i2]==M31T[i][1] && M[j][i3]==M31T[i][2])
           {r[ri]=j;
            ri++;
            if(i==m1-1)
             { c[0]=i1;c[1]=i2;c[2]=i3;
               j=n;
               flag1=1;
             }
            break;
           } 
        }
        if(j==m)
        { break;}
      }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[1]]=1;
  temp=freqr[r[0]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[1]]=0;

   M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;
  
  M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;
 
   M1[r[2]][c[2]]=1;
  temp=freqr[r[2]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[2]]=0;

   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[3]][c[1]]=1;
  temp=freqr[r[3]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[1]]=0;

  return;
}

 
// Checking for the forbidden submatrix M31
  int M31[3][4]={1,1,0,0,0,1,1,0,0,1,0,1};
  m1=3;
  n1=4;
  r[0]=r[1]=r[2]=-1;
  c[0]=c[1]=c[2]=c[3]=-1;
  ri=0;
  ci=0;


flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++)//Considering submatrix of columns with indices i1,i2,i3  
    { if(i1==i3) continue;
      if(i2==i3) continue;
      ri=0;ci=0;
      for(i=0;i<n1;i++)
      { for(j=0;j<n;j++)//Checking whether all the rows of M31 are present in the sumatrix induced by columns with indices i1,i2,i3
        { if(M[i1][j]==M31[0][i] && M[i2][j]==M31[1][i] && M[i3][j]==M31[2][i])
           {c[ci]=j;
            ci++;
            if(i==n1-1)
             { r[0]=i1;r[1]=i2;r[2]=i3;
               j=n;
               flag1=1;
             }
            break;
           } 
        }
        if(j==n)
        { break;}
      }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;

   M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
  
  M1[r[1]][c[0]]=1;
  temp=freqr[r[1]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[0]]=0;
 
   M1[r[1]][c[3]]=1;
  temp=freqr[r[1]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[3]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[2]][c[2]]=1;
  temp=freqr[r[2]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[2]]=0;

  return;
}


//Checking for the forbidden submatrix M21
  int M21[4][4]={1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,1};
  m1=4;
  n1=4;
  r[0]=r[1]=r[2]=r[3]=-1;
  c[0]=c[1]=c[2]=c[3]=-1;
  ri=0;
  ci=0;


flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++)  
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)//Considering submatrix of rows with indices i1,i2,i3,i4
      {
      if(i1==i4) continue;
      if(i2==i4) continue;
      if(i3==i4) continue;
      ri=0;ci=0;
      for(i=0;i<n1;i++)
      { for(j=0;j<n;j++)//Checking whether all the columns of M21 are present in the sumatrix induced by rows with indices i1,i2,i3,i4
        { if(M[i1][j]==M21[0][i] && M[i2][j]==M21[1][i] && M[i3][j]==M21[2][i] && M[i4][j]==M21[3][i])
           {c[ci]=j;
            ci++;
            if(i==n1-1)
             { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;
               j=n;
               flag1=1;
             }
            break;
           } 
        }
        if(j==n)
        { break;}
      }
      if(flag1==1)
       break;
      }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;

   M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
  
  M1[r[1]][c[0]]=1;
  temp=freqr[r[1]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[0]]=0;
 
   M1[r[1]][c[3]]=1;
  temp=freqr[r[1]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[3]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[3]][c[2]]=1;
  temp=freqr[r[3]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[2]]=0;

  return;
}


//Checking for the forbidden submatrix M21 Transpose
  int M21T[4][4]={1,0,0,1,1,1,1,1,0,1,1,0,0,0,1,1};
  m1=4;
  n1=4;
  r[0]=r[1]=r[2]=r[3]=-1;
  c[0]=c[1]=c[2]=c[3]=-1;
  ri=0;
  ci=0;


flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++)  
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)//Considering submatrix of rows with indices i1,i2,i3,i4
      {
      if(i1==i4) continue;
      if(i2==i4) continue;
      if(i3==i4) continue;
      ri=0;ci=0;
      for(i=0;i<n1;i++)
      { for(j=0;j<n;j++)//Checking whether all the columns of M21T are present in the sumatrix induced by rows with indices i1,i2,i3,i4
        { if(M[i1][j]==M21T[0][i] && M[i2][j]==M21T[1][i] && M[i3][j]==M21T[2][i] && M[i4][j]==M21T[3][i])
           {c[ci]=j;
            ci++;
            if(i==n1-1)
             { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;
               j=n;
               flag1=1;
             }
            break;
           } 
        }
        if(j==n)
        { break;}
      }
      if(flag1==1)
       break;
      }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[1]]=1;
  temp=freqr[r[0]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[1]]=0;

   M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;
  
  M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;
 
   M1[r[2]][c[3]]=1;
  temp=freqr[r[2]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[3]]=0;

   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[3]][c[1]]=1;
  temp=freqr[r[3]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[1]]=0;

  return;
}

//Checking for the forbidden submatrix M22
  int M22[5][5]={1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,1};
  m1=5;
  n1=5;
  r[0]=r[1]=r[2]=r[3]=r[4]=-1;
  c[0]=c[1]=c[2]=c[3]=c[4]=-1;
  ri=0;
  ci=0;

flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++) 
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)
      {
        if(i1==i4) continue;
        if(i2==i4) continue;
        if(i3==i4) continue;
        for(i5=0;i5<m;i5++)//Considering submatrix of rows with indices i1,i2,i3,i4,i5
        {
          if(i1==i5) continue;
          if(i2==i5) continue;
          if(i3==i5) continue; 
          if(i4==i5) continue;
          ri=0;ci=0;
          for(i=0;i<n1;i++)//Checking whether all the columns of M22 are present in the sumatrix induced by rows with indices i1,i2,i3,i4,i5
          { for(j=0;j<n;j++)
            { if(M[i1][j]==M22[0][i] && M[i2][j]==M22[1][i] && M[i3][j]==M22[2][i] && M[i4][j]==M22[3][i] && M[i5][j]==M22[4][i])
               {c[ci]=j;
                ci++;
                if(i==n1-1)
                 { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;r[4]=i5;
                   j=n;
                   flag1=1;
                 }
                break;
               } 
            }
            if(j==n)
            { break;}
          }
          if(flag1==1)
           break;
          }
        if(flag1==1)
           break;
        }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;

   M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
  
  M1[r[0]][c[4]]=1;
  temp=freqr[r[0]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[4]]=0;
 
   M1[r[1]][c[0]]=1;
  temp=freqr[r[1]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[0]]=0;

   M1[r[1]][c[3]]=1;
  temp=freqr[r[1]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[3]]=0;

   M1[r[1]][c[4]]=1;
  temp=freqr[r[1]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[4]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[2]][c[1]]=1;
  temp=freqr[r[2]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[1]]=0;
  
  M1[r[2]][c[4]]=1;
  temp=freqr[r[2]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[4]]=0;
 
   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[4]][c[3]]=1;
  temp=freqr[r[4]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[3]]=0;


  return;
}

//Checking for the forbidden submatrix M22 Transpose
  int M22T[5][5]={1,0,0,0,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1};
  m1=5;
  n1=5;
  r[0]=r[1]=r[2]=r[3]=r[4]=-1;
  c[0]=c[1]=c[2]=c[3]=c[4]=-1;
  ri=0;
  ci=0;


flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++)
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)
      {
        if(i1==i4) continue;
        if(i2==i4) continue;
        if(i3==i4) continue;
        for(i5=0;i5<m;i5++)//Considering submatrix of rows with indices i1,i2,i3,i4,i5
        {
          if(i1==i5) continue;
          if(i2==i5) continue;
          if(i3==i5) continue; 
          if(i4==i5) continue;
          ri=0;ci=0;
          for(i=0;i<n1;i++)
          { for(j=0;j<n;j++)//Checking whether all the columns of M22T are present in the sumatrix induced by rows with indices i1,i2,i3,i4,i5
            { if(M[i1][j]==M22T[0][i] && M[i2][j]==M22T[1][i] && M[i3][j]==M22T[2][i] && M[i4][j]==M22T[3][i] && M[i5][j]==M22T[4][i])
               {c[ci]=j;
                ci++;
                if(i==n1-1)
                 { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;r[4]=i5;
                   j=n;
                   flag1=1;
                 }
                break;
               } 
            }
            if(j==n)
            { break;}
          }
          if(flag1==1)
           break;
          }
        if(flag1==1)
           break;
        }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[1]]=1;
  temp=freqr[r[0]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[1]]=0;

   M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;
  
  M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
 
   M1[r[1]][c[2]]=1;
  temp=freqr[r[1]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[2]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[3]][c[1]]=1;
  temp=freqr[r[3]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[1]]=0;

   M1[r[3]][c[4]]=1;
  temp=freqr[r[3]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[4]]=0;
  
  M1[r[4]][c[0]]=1;
  temp=freqr[r[4]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[0]]=0;
 
   M1[r[4]][c[1]]=1;
  temp=freqr[r[4]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[1]]=0;

   M1[r[4]][c[2]]=1;
  temp=freqr[r[4]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[2]]=0;


  return;
}

//Checking for the forbidden submatrix M32
  int M32[4][5]={1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1};
  m1=4;
  n1=5;
  r[0]=r[1]=r[2]=r[3]=-1;
  c[0]=c[1]=c[2]=c[3]=c[4]=-1;
  ri=0;
  ci=0;

flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++) 
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)//Considering submatrix of rows with indices i1,i2,i3,i4
      {
      if(i1==i4) continue;
      if(i2==i4) continue;
      if(i3==i4) continue;
      ri=0;ci=0;
      for(i=0;i<n1;i++)
      { for(j=0;j<n;j++)//Checking whether all the columns of M32 are present in the sumatrix induced by rows with indices i1,i2,i3,i4
        { if(M[i1][j]==M32[0][i] && M[i2][j]==M32[1][i] && M[i3][j]==M32[2][i] && M[i4][j]==M32[3][i])
           {c[ci]=j;
            ci++;
            if(i==n1-1)
             { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;
               j=n;
               flag1=1;
             }
            break;
           } 
        }
        if(j==n)
        { break;}
      }
      if(flag1==1)
       break;
      }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;

   M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
  
  M1[r[0]][c[4]]=1;
  temp=freqr[r[0]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[4]]=0;
 
   M1[r[1]][c[0]]=1;
  temp=freqr[r[1]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[0]]=0;

   M1[r[1]][c[3]]=1;
  temp=freqr[r[1]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[3]]=0;

   M1[r[1]][c[4]]=1;
  temp=freqr[r[1]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[4]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[2]][c[1]]=1;
  temp=freqr[r[2]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[1]]=0;
  
  M1[r[2]][c[4]]=1;
  temp=freqr[r[2]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[4]]=0;
 
   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[3]][c[3]]=1;
  temp=freqr[r[3]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[3]]=0;


  return;
}

// Checking for the forbidden submatrix M32 Transpose
  int M32T[5][4]={1,0,0,0,1,1,0,1,0,1,1,1,0,0,1,0,0,0,0,1};
  m1=5;
  n1=4;
  r[0]=r[1]=r[2]=r[3]=r[4]=-1;
  c[0]=c[1]=c[2]=c[3]=-1;
  ri=0;
  ci=0;

flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++)  
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)
      {
        if(i1==i4) continue;
        if(i2==i4) continue;
        if(i3==i4) continue;
        for(i5=0;i5<m;i5++)//Considering submatrix of rows with indices i1,i2,i3,i4,i5 
        {
          if(i1==i5) continue;
          if(i2==i5) continue;
          if(i3==i5) continue; 
          if(i4==i5) continue;
          ri=0;ci=0;
          for(i=0;i<n1;i++)
          { for(j=0;j<n;j++)//Checking whether all the columns of M32T are present in the sumatrix induced by rows with indices i1,i2,i3,i4,i5
            { if(M[i1][j]==M32T[0][i] && M[i2][j]==M32T[1][i] && M[i3][j]==M32T[2][i] && M[i4][j]==M32T[3][i] && M[i5][j]==M32T[4][i])
               {c[ci]=j;
                ci++;
                if(i==n1-1)
                 { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;r[4]=i5;
                   j=n;
                   flag1=1;
                 }
                break;
               } 
            }
            if(j==n)
            { break;}
          }
          if(flag1==1)
           break;
          }
        if(flag1==1)
           break;
        }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[1]]=1;
  temp=freqr[r[0]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[1]]=0;

   M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;
  
  M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
 
   M1[r[1]][c[2]]=1;
  temp=freqr[r[1]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[2]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[3]][c[1]]=1;
  temp=freqr[r[3]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[1]]=0;

   M1[r[3]][c[3]]=1;
  temp=freqr[r[3]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[3]]=0;
  
  M1[r[4]][c[0]]=1;
  temp=freqr[r[4]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[0]]=0;
 
   M1[r[4]][c[1]]=1;
  temp=freqr[r[4]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[1]]=0;

   M1[r[4]][c[2]]=1;
  temp=freqr[r[4]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[2]]=0;


  return;
}

//Checking for the forbidden submatrix M33
  int M33[5][6]={1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,0,1};
  m1=5;
  n1=6;
  r[0]=r[1]=r[2]=r[3]=r[4]=-1;
  c[0]=c[1]=c[2]=c[3]=c[4]=c[5]=-1;
  ri=0;
  ci=0;

flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++) 
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)
      {
        if(i1==i4) continue;
        if(i2==i4) continue;
        if(i3==i4) continue;
        for(i5=0;i5<m;i5++)//Considering submatrix of rows with indices i1,i2,i3,i4,i5
        {
          if(i1==i5) continue;
          if(i2==i5) continue;
          if(i3==i5) continue; 
          if(i4==i5) continue;
          ri=0;ci=0;
          for(i=0;i<n1;i++)//Checking whether all the columns of M33 are present in the sumatrix induced by rows with indices i1,i2,i3,i4,i5
          { for(j=0;j<n;j++)
            { if(M[i1][j]==M33[0][i] && M[i2][j]==M33[1][i] && M[i3][j]==M33[2][i] && M[i4][j]==M33[3][i] && M[i5][j]==M33[4][i])
               {c[ci]=j;
                ci++;
                if(i==n1-1)
                 { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;r[4]=i5;
                   j=n;
                   flag1=1;
                 }
                break;
               } 
            }
            if(j==n)
            { break;}
          }
          if(flag1==1)
           break;
          }
        if(flag1==1)
           break;
        }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }

//Branching on 0's
  M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;

   M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
  
  M1[r[0]][c[4]]=1;
  temp=freqr[r[0]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[4]]=0;
 
   M1[r[0]][c[5]]=1;
  temp=freqr[r[0]]*freqc[c[5]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[5]]=0;

   M1[r[1]][c[0]]=1;
  temp=freqr[r[1]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[0]]=0;

   M1[r[1]][c[3]]=1;
  temp=freqr[r[1]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[3]]=0;

   M1[r[1]][c[4]]=1;
  temp=freqr[r[1]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[4]]=0;

   M1[r[1]][c[5]]=1;
  temp=freqr[r[1]]*freqc[c[5]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[5]]=0;
  
  M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;
 
   M1[r[2]][c[1]]=1;
  temp=freqr[r[2]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[1]]=0;

   M1[r[2]][c[4]]=1;
  temp=freqr[r[2]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[4]]=0;

   M1[r[2]][c[5]]=1;
  temp=freqr[r[2]]*freqc[c[5]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[5]]=0;

   M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;

   M1[r[3]][c[1]]=1;
  temp=freqr[r[3]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[1]]=0;
  
  M1[r[3]][c[2]]=1;
  temp=freqr[r[3]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[2]]=0;
 
   M1[r[3]][c[5]]=1;
  temp=freqr[r[3]]*freqc[c[5]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[5]]=0;

   M1[r[4]][c[0]]=1;
  temp=freqr[r[4]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[0]]=0;

  M1[r[4]][c[4]]=1;
  temp=freqr[r[4]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[4]]=0;



  return;
}

// Checking for the forbidden submatrix M33 Transpose
  int M33T[6][5]={1,0,0,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,1,1,0,0,0,1,0,0,0,0,0,1};
  m1=6;
  n1=5;
  r[0]=r[1]=r[2]=r[3]=r[4]=r[5]=-1;
  c[0]=c[1]=c[2]=c[3]=c[4]=-1;
  ri=0;
  ci=0;

flag1=0;
for(i1=0;i1<m;i1++)
{ for(i2=0;i2<m;i2++)
  { if(i1==i2) continue;
    for(i3=0;i3<m;i3++) 
    { if(i1==i3) continue;
      if(i2==i3) continue;
      for(i4=0;i4<m;i4++)
      {
        if(i1==i4) continue;
        if(i2==i4) continue;
        if(i3==i4) continue;
        for(i5=0;i5<m;i5++)
        {
          if(i1==i5) continue;
          if(i2==i5) continue;
          if(i3==i5) continue; 
          if(i4==i5) continue;
            for(i6=0;i6<m;i6++)//Considering submatrix of rows with indices i1,i2,i3,i4,i5,i6
            {
              if(i1==i6) continue;
              if(i2==i6) continue;
              if(i3==i6) continue; 
              if(i4==i6) continue;
              if(i5==i6) continue;
              ri=0;ci=0;
             for(i=0;i<n1;i++)//Checking whether all the columns of M33T are present in the sumatrix induced by rows with indices i1,i2,i3,i4,i5,i6
             { for(j=0;j<n;j++)
              { if(M[i1][j]==M33T[0][i] && M[i2][j]==M33T[1][i] && M[i3][j]==M33T[2][i] && M[i4][j]==M33T[3][i] && M[i5][j]==M33T[4][i] && M[i6][j]==M33T[5][i])
                 {c[ci]=j;
                  ci++;
                  if(i==n1-1)
                   { r[0]=i1;r[1]=i2;r[2]=i3;r[3]=i4;r[4]=i5;r[5]=i6;
                     j=n;
                     flag1=1;
                   }
                  break;
                 } 
              }
              if(j==n)
              { break;}
            }
            if(flag1==1)
             break;
          }
          if(flag1==1)
             break;
         }
        if(flag1==1)
           break;
        }
     if(flag1==1)
       break;
    }
    if(flag1==1)
       break;
  }
  if(flag1==1)
       break;
}

if(flag1==1)
{ 
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }
//Branching on 0's
  M1[r[0]][c[1]]=1;
  temp=freqr[r[0]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[1]]=0;

  M1[r[0]][c[2]]=1;
  temp=freqr[r[0]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[2]]=0;

   M1[r[0]][c[3]]=1;
  temp=freqr[r[0]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[3]]=0;
  
  M1[r[0]][c[4]]=1;
  temp=freqr[r[0]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[0]][c[4]]=0;
 

   M1[r[1]][c[2]]=1;
  temp=freqr[r[1]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[2]]=0;

   M1[r[1]][c[3]]=1;
  temp=freqr[r[1]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[1]][c[3]]=0;

   M1[r[2]][c[0]]=1;
  temp=freqr[r[2]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[0]]=0;

   M1[r[2]][c[3]]=1;
  temp=freqr[r[2]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[2]][c[3]]=0;
  
  M1[r[3]][c[0]]=1;
  temp=freqr[r[3]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[0]]=0;
 
   M1[r[3]][c[1]]=1;
  temp=freqr[r[3]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[3]][c[1]]=0;

   M1[r[4]][c[0]]=1;
  temp=freqr[r[4]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[0]]=0;

   M1[r[4]][c[1]]=1;
  temp=freqr[r[4]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[1]]=0;

   M1[r[4]][c[2]]=1;
  temp=freqr[r[4]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[2]]=0;

   M1[r[4]][c[4]]=1;
  temp=freqr[r[4]]*freqc[c[4]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[4]][c[4]]=0;
  
  M1[r[5]][c[0]]=1;
  temp=freqr[r[5]]*freqc[c[0]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[5]][c[0]]=0;
 
   M1[r[5]][c[1]]=1;
  temp=freqr[r[5]]*freqc[c[1]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[5]][c[1]]=0;

   M1[r[5]][c[2]]=1;
  temp=freqr[r[5]]*freqc[c[2]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[5]][c[2]]=0;

  M1[r[5]][c[3]]=1;
  temp=freqr[r[5]]*freqc[c[3]];
  ksc1p0e(M1,m,n,k-temp);
  M1[r[5]][c[3]]=0;



  return;
}


// Checking for forbidden matrices of the type M1k and M1k transpose

   int **Gm,*hole,f1;
   Gm=(int**)malloc((m+n)*sizeof(int*));
   hole=(int*)malloc((m+n+1)*sizeof(int));
   for(i=0;i<m+n;i++)
   { Gm[i]=(int*)malloc((m+n)*sizeof(int));
   }
  //Initializing Gm
  for(i=0;i<m+n;i++)
  { for(j=0;j<m+n;j++)
    { Gm[i][j]=0;
    }
  }


for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
   { M1[i][j]=M[i][j];
   }
  }



  //Constructing Gm from M
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++)
    { Gm[i][j+m]=M1[i][j];
      Gm[j+m][i]=M1[i][j];
    }
  }


  hole=findHole(Gm,m,n);

  //If the graph dosent have a hole, hole[0] has the value -1 else if the size of the hole is h, hole[0] contains the value h+2 and hole[1...(h+1)] contains the vertices forming the hole.
  if(hole[0]==-1)
  { if(k>=0)
    { flag=1;
      for(i=0;i<m;i++)
      { for(j=0;j<n;j++) printf("%d ",M[i][j]);
        printf("\n");}printf("\n");
    }
  }

  else
  {  if((hole[0]-2)/2-2>k)
     { k=-1;
     }
     else 
    {  
       for(i=1;i<hole[0]-1;i++)
        { for(j=i+3;j<hole[0]-1;j+=2)
          { if(i==1 && j==hole[0]-2) continue;
            if(hole[i]<m)
            { f1=freqr[hole[i]]*freqc[hole[j]-m];
              M1[hole[i]][hole[j]-m]=1;
              ksc1p0e(M1,m,n,k-f1);
              M1[hole[i]][hole[j]-m]=0;          
            }
            else
            { f1=freqr[hole[j]]*freqc[hole[i]-m];
              M1[hole[j]][hole[i]-m]=1;
              ksc1p0e(M1,m,n,k-f1);
              M1[hole[j]][hole[i]-m]=0;
            }
          }
        }
     }   

  }


}


int* findHole(int **G,int m,int n)
{ int r1,c1,r2,c2,i,j,dr1,dr2,dc1,dc2,**G1,*hole,temp;
  hole=(int*)malloc((m+n)*sizeof(int));
  hole[0]=-1;
  
  G1=(int**)malloc((m+n)*sizeof(int*));
  for(i=0;i<(m+n);i++)
   G1[i]=(int*)malloc((m+n)*sizeof(int));
  
  for(r1=0;r1<m;r1++)
 {
   for(c1=m;c1<m+n;c1++)
  { 
    if(G[r1][c1]==1)
   { 
     for(r2=0;r2<m;r2++)
    { 
      if(r1==r2) continue;
      if(G[c1][r2]==1)
     {
       for(c2=m;c2<m+n;c2++)
       { 
         if(c1==c2) continue;
         if(G[r2][c2]==1)
        { 
          dr1=0;dr2=0;dc1=0;dc2=0;
          //Checking whether the induced graph on r1,c1,r2,c2 forms a P4.
          dr1=G[r1][r2]+G[r1][c1]+G[r1][c2];
          dr2=G[r2][r1]+G[r2][c1]+G[r2][c2];
          dc1=G[c1][r1]+G[c1][r2]+G[c1][c2];
          dc2=G[c2][r1]+G[c2][r2]+G[c2][c1];
         
          if(dr1==1 && dr2==2 && dc1==2 && dc2==1)
           { 
             for(i=0;i<m+n;i++)
             { for(j=0;j<m+n;j++)
               { G1[i][j]=G[i][j];
               }
             }             

            //Constructing G1=G\((N[c1] U N[r2])\{r1,c2})
              for(i=0;i<m+n;i++)
            { 
              if(i==r1) continue;
              if(i==c2) continue;
              if(G[c1][i]==1)
              { for(j=0;j<m+n;j++)
                { G1[i][j]=0;G1[j][i]=0;}
              }
              if(G[r2][i]==1)
              { for(j=0;j<m+n;j++)
                { G1[i][j]=0;G1[j][i]=0;}
              }
            }
           //Finding the path from c2 to r1 in G1 if there exists one
            hole=findpath(c2,r1,G1,(m+n));
            if(hole[0]!=-1)
             { temp=hole[0];
               hole[temp]=c1;
               hole[temp+1]=r2;
               hole[temp+2]=c2;
               hole[0]=temp+3;
               return hole;
             }
           }
        }
       }
     }
    }
   }
  }
 }
 return hole;
}

//Function to find the path from s to d in G 
int* findpath(int s,int d,int **G,int n)
{ int *visited,i,index,*path;
  path=(int*)malloc(n*sizeof(int));
  visited=(int*)malloc(n*sizeof(int));
  for(i=0;i<n;i++)
   visited[i]=0;

  path[0]=-1;
  index=1;
  path=find(s,d,G,n,path,visited,index);
  return path;
}

int* find(int s,int d,int **G,int n,int *path,int *visited,int index)
{ int i;
  visited[s]=1;
  path[index]=s;
  index++;

  if(s==d)
  { path[0]=index;
    return path;
  }
  else
  { for(i=0;i<n;i++)
    { if(G[s][i]==1)
     { if(visited[i]==0)
         return find(i,d,G,n,path,visited,index);
     }
    }
  }
 index--;
 visited[s]=0;
 return path;
}




