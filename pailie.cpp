/*****************************************************************
 *   Copyright (C) 2019 * Ltd. All rights reserved.
 *   
 *   File name   : pailie.cpp
 *   Author      : qujiale
 *   Created date: 2019-07-01
 *   Description : 排列子序列 
 *
 *****************************************************************/

#include<iostream>
#include<vector>
using namespace std;
int main()
{
  int n;
  cin>>n;
  vector<int> v;
  v.resize(n);
  for(int i = 0; i < n; ++i)
  {
    cin>>v[i];
  }
  int ret = 1;
  for(int i=1; i<n-1; i++)
  {
    //找出波峰波谷
    if((v[i-1] < v[i] && v[i] > v[i+1])
    || (v[i-1] > v[i] && v[i] < v[i+1]))
    {
      ret++;
      // 这里对应处理的就是上面情况二描述的问题
      if(i != n-3)
        i++;
    }
  }
  cout<<ret<<endl;
}




