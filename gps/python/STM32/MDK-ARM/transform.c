#include "transform.h"

static const double pi = 3.141592653589793238426;
static const double a = 6378245.0;
static const double ee = 0.00669342162296594323;
static const double x_pi = 3.14159265358979324 * 3000.0 / 180.0;

/******************************************************************************
function:	
	Latitude conversion
******************************************************************************/
static double transformLat(double x,double y)
{
		double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 *sqrt(abs(x));
		ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
		ret += (20.0 * sin(y * pi) + 40.0 * sin(y / 3.0 * pi)) * 2.0 / 3.0;
		ret += (160.0 * sin(y / 12.0 * pi) + 320 * sin(y * pi / 30.0)) * 2.0 / 3.0;
		return ret;
}

/******************************************************************************
function:	
	Longitude conversion
******************************************************************************/
static double transformLon(double x,double y)
{
		double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(abs(x));
		ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
		ret += (20.0 * sin(x * pi) + 40.0 * sin(x / 3.0 * pi)) * 2.0 / 3.0;
		ret += (150.0 * sin(x / 12.0 * pi) + 300.0 * sin(x / 30.0 * pi)) * 2.0 / 3.0;
		return ret;
}

/******************************************************************************
function:	
	GPS's WGS-84 standard is converted into GCJ-02 international standard
******************************************************************************/
Coordinates wgs84_to_gcj02(Coordinates gps)
{
		Coordinates gg;
		double dLat = transformLat(gps.Lon - 105.0, gps.Lat - 35.0);
		double dLon = transformLon(gps.Lon - 105.0, gps.Lat - 35.0);
		double radLat = gps.Lat / 180.0 * pi;
		double magic = sin(radLat);
		magic = 1 - ee * magic * magic;
		double sqrtMagic = sqrt(magic);
		dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
		dLon = (dLon * 180.0) / (a / sqrtMagic * cos(radLat) * pi);
		gg.Lat = gps.Lat + dLat;
		gg.Lon = gps.Lon + dLon;
		return gg;
}

/******************************************************************************
function:	
	GCJ-02 international standard converted to Baidu map BD-09 standard
******************************************************************************/
Coordinates gcj02_to_bd09(Coordinates gg)
{
		Coordinates bd;
		double x = gg.Lon, y = gg.Lat;
		double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);
		double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);
		bd.Lon = z * cos(theta) + 0.0065;
		bd.Lat = z * sin(theta) + 0.006;
		return bd;
}

