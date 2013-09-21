
class M8Date
{
private:
	int year;
	int month;
	int day;
	int week;
	int dayweek;

public:
	M8Date(int year_first,int month_first,int day_first,int dayweek_first)
	{
		this->year=year_first;
		this->month=month_first;
		this->day=day_first;
		this->dayweek=dayweek_first;
		this->week=1;
	}

	M8Date NextDay(M8Date &mdate)
	{
		if(((mdate.month==1)||(mdate.month==3)||(mdate.month==5)||(mdate.month==7)||(mdate.month==8)||(mdate.month==10)||(mdate.month==12))&&(mdate.day<31))
		{
			mdate.dayweek=(mdate.dayweek%7)+1;
			mdate.week+=(mdate.dayweek==1);
			mdate.day+=1;
			return mdate;
		}
		else if(((mdate.month==4)||(mdate.month==6)||(mdate.month==9)||(mdate.month==11))&&(mdate.day<30))
		{
			mdate.dayweek=(mdate.dayweek%7)+1;
			mdate.week+=(mdate.dayweek==1);
			mdate.day+=1;
			return mdate;
		}
		else if((mdate.month==2)&&(mdate.day<(28+((mdate.year%4==0)&&(mdate.year%100!=0)||(mdate.year%400==0)))))
		{
			mdate.dayweek=(mdate.dayweek%7)+1;
			mdate.week+=(mdate.dayweek==1);
			mdate.day+=1;
			return mdate;
		}
		else 
		{
			if(mdate.month<12)
			{
				mdate.dayweek=(mdate.dayweek%7)+1;
				mdate.week+=(mdate.dayweek==1);
				mdate.day=1;
				mdate.month+=1;
				return mdate;
			}
			else if(mdate.month==12)
			{
				mdate.dayweek=(mdate.dayweek%7)+1;
				mdate.week+=(mdate.dayweek==1);
				mdate.day=1;
				mdate.month=1;
				mdate.year+=1;
				return mdate;
			}
		}
	}

	int Getyear()
	{
		return this->year;
	}

	int Getmonth()
	{
		return this->month;
	}

	int Getday()
	{
		return this->day;
	}

	int Getweek()
	{
		return this->week;
	}

	int Getdayweek()
	{
		return this->dayweek;
	}

	//这里是一个静态共有的函数成员,以获得当前日期
	static CMzString DateToday()
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		CMzString sDate;
		wsprintf(sDate.C_Str(), L"%4d%02d%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);    
		
		return sDate;
	}


};

