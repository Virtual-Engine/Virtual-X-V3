


namespace VX
{
	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsOutdoor[56] = {
		{ "IAA Roof", 134.085,-637.859,262.851 },
		{ "FIB Roof", 150.126,-754.591,262.865 },
		{ "Maze Bank Roof", -75.015,-818.215,326.176 },
		{ "Top Of The Mt Chilad", 450.718,5566.614,806.183 },
		{ "Most Northerly Point", 24.775,7644.102,19.055 },
		{ "Vinewood Bowl Stage", 686.245,577.950,130.461 },
		{ "Sisyphus Theater Stage", 205.316,1167.378,227.005 },
		{ "Galileo Observatory Roof", -438.804,1076.097,352.411 },
		{ "Kortz Center", -2243.810,264.048,174.615 },
		{ "Chumash Historic", -3426.683,967.738,8.347 },
		{ "Paleto Bay Pier", -275.522,6635.835,7.425 },
		{ "God's thumb", -1006.402,6272.383,1.503 },
		{ "Calafia Train Bridge", -517.869,4425.284,89.795 },
		{ "Altruist Cult Camp", -1170.841,4926.646,224.295 },
		{ "Maze Bank Arena Roof", -324.300,-1968.545,67.002 },
		{ "Marlowe Vineyards", -1868.971,2095.674,139.115 },
		{ "Hippy Camp", 2476.712,3789.645,41.226 },
		{ "Devin Weston's House", -2639.872,1866.812,160.135 },
		{ "Abandon Mine", -595.342,2086.008,131.412 },
		{ "Weed Farm", 2208.777,5578.235,53.735 },
		{ "Stab City", 126.975,3714.419,46.827 },
		{ "Airplane Graveyard Airplane Tail", 2395.096,3049.616,60.053 },
		{ "Satellite Dish Antenna", 2034.988,2953.105,74.602 },
		{ "Satellite Dishes", 2062.123,2942.055,47.431 },
		{ "Windmill Top", 2026.677,1842.684,133.313 },
		{ "Sandy Shores Building Site Crane", 1051.209,2280.452,89.727 },
		{ "Rebel Radio", 736.153,2583.143,79.634 },
		{ "Quarry", 2954.196,2783.410,41.004 },
		{ "Palmer-Taylor Power Station Chimney", 2732.931,1577.540,83.671 },
		{ "Merryweather Dock", 486.417,-3339.692,6.070 },
		{ "Cargo Ship", 899.678,-2882.191,19.013 },
		{ "Del Perro Pier", -1850.127,-1231.751,13.017 },
		{ "Play Boy Mansion", -1475.234,167.088,55.841 },
		{ "Jolene Cranley-Evans Ghost", 3059.620,5564.246,197.091 },
		{ "NOOSE Headquarters", 2535.243,-383.799,92.993 },
		{ "Snowman", 971.245,-1620.993,30.111 },
		{ "Oriental Theater", 293.089,180.466,104.301 },
		{ "Beach Skatepark", -1374.881,-1398.835,6.141 },
		{ "Underpass Skatepark", 718.341,-1218.714,26.014 },
		{ "Casino", 925.329,46.152,80.908 },
		{ "University of San Andreas", -1696.866,142.747,64.372 },
		{ "La Puerta Freeway Bridge", -543.932,-2225.543,122.366 },
		{ "Land Act Dam", 1660.369,-12.013,170.020 },
		{ "Mount Gordo", 2877.633,5911.078,369.624 },
		{ "Little Seoul", -889.655,-853.499,20.566 },
		{ "Epsilon Building", -695.025,82.955,55.855 },
		{ "The Richman Hotel", -1330.911,340.871,64.078 },
		{ "Vinewood Sign", 711.362,1198.134,348.526 },
		{ "Los Santos Golf Club", -1336.715,59.051,55.246 },
		{ "Chicken", -31.010,6316.830,40.083 },
		{ "Little Portola", -635.463,-242.402,38.175 },
		{ "Pacific Bluffs Country Club", -3022.222,39.968,13.611 },
		{ "Paleto Forest Sawmill Chimney", -549.467,5308.221,114.146 },
		{ "Mirror Park", 1070.206,-711.958,58.483 },
		{ "Rocket", 1608.698,6438.096,37.637 },
		{ "El Gordo Lighthouse", 3430.155,5174.196,41.280 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsIndoor[16] = {
		{ "Strip Club DJ Booth", 126.135,-1278.583,29.270 },
		{ "Blaine County Savings Bank", -109.299,6464.035,31.627 },
		{ "Police Station", 436.491,-982.172,30.699 },
		{ "Humane Labs Tunnel", 3525.495,3705.301,20.992 },
		{ "Ammunation Office", 12.494,-1110.130,29.797 },
		{ "Ammunation Gun Range", 22.153,-1072.854,29.797 },
		{ "Trevor's Meth Lab", 1391.773,3608.716,38.942 },
		{ "Pacific Standard Bank Vault", 255.851,217.030,101.683 },
		{ "Lester's House", 1273.898,-1719.304,54.771 },
		{ "Floyd's Apartment", -1150.703,-1520.713,10.633 },
		{ "FIB Top Floor", 135.733,-749.216,258.152 },
		{ "IAA Office", 117.220,-620.938,206.047 },
		{ "Pacific Standard Bank", 235.046,216.434,106.287 },
		{ "Fort Zancudo ATC Entrance", -2344.373,3267.498,32.811 },
		{ "Fort Zancudo ATC Top Floor", -2358.132,3249.754,101.451 },
		{ "Torture Room", 147.170,-2201.804,4.688 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsLSC[6] = {
		{ "Benny's Garage", -206.91985,-1300.7858,31.29598 },
		{ "Beekers Garage", 120.13485,6616.1055,31.850428 },
		{ "Sandy Shores", 1174.49,2658.1643,38.070953 },
		{ "Grand Senora Dust", -1136.742,-1982.3253,13.164545 },
		{ "Burton", -375.6223,-128.76067,38.684124 },
		{ "La Mesa", 707.62823,-1087.7771,22.433643 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsCS[13] = {
		{ "Paleto Bay", -4.509100,6521.252930,30.571024 },
		{ "Grapeseed", 1678.057495,4819.882324,41.299820 },
		{ "Grand Senora", 1179.679688,2691.378662,37.124043 },
		{ "Great Chaparral", -1089.404785,2697.033447,19.442095 },
		{ "Suburban Havick", 134.122055,-200.211334,53.864090 },
		{ "Ponsonbys Burton", -148.234741,-308.074463,38.104240 },
		{ "Ponsonbys Rockford Hills", -725.551453,-162.833710,36.570301 },
		{ "Ponsonbys Morningwood", -1460.654419,-227.550964,48.728519 },
		{ "Suburban Del Perro", -1210.620361,-784.160217,16.549015 },
		{ "Masks Vespucci Beach", -1342.185913,-1280.013428,4.443256 },
		{ "Binco Vespucci", -814.432800,-1085.986938,10.567306 },
		{ "Binco Strawberry", 411.403564,-806.654907,28.742212 },
		{ "Strawberry", 89.320786,-1392.317627,28.800083 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsTS[6] = {
		{ "Paleto Bay", -285.910400,6202.941895,30.626459 },
		{ "Sandy Shores", 1853.771851,3746.440918,32.395195 },
		{ "Chumash", -3155.888672,1073.844482,20.188726 },
		{ "Vinewood", 318.228790,164.457535,103.146561 },
		{ "Vespucci", -1163.504639,-1413.232788,4.360025 },
		{ "El Burro Heights", 1318.160889,-1642.176147,51.787762 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsStores[9] = {
		{ "Banham Canyon", -3037.177246, 590.165283, 7.78449 },
		{ "Chumash", -3237.171387, 1004.163879, 12.354364 },
		{ "Grand Senora Desert", 2683.951172, 3281.507324, 55.347145 },
		{ "Harmony", 543.490784, 2675.008301, 42.162228 },
		{ "Mount Chiliad", 1730.461914, 6410.027344, 35.384476 },
		{ "Sandy Shores", 1966.198853, 3738.300537, 32.251864 },
		{ "Strawberry", 28.123456, -1351.123456, 29.123456 },
		{ "Tataviam Mountains", 2561.452881, 384.998932, 108.532890 },
		{ "Vinewood", 376.287079, 322.833252, 103.418564 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsAmmo[11] = {
		{ "Paleto Bay", -318.859039,6074.433105,30.614943 },
		{ "Sandy Shores", 1704.671997,3748.880615,33.286053 },
		{ "Great Chaparral", -1108.600830,2685.694092,18.177374 },
		{ "Chumash", -3155.888672,1073.844482,20.188726 },
		{ "Palomino Fwy", 2571.371826,313.879608,107.970573 },
		{ "Hawick", 235.666794,-42.263149,69.221313 },
		{ "Morningwood", -1328.592896,-387.114410,36.126881 },
		{ "Little Seoul", -665.232727,-952.522522,20.866556 },
		{ "La Mesa", 844.439026,-1009.422424,27.511728 },
		{ "Pillbox Hill", 17.377790,-1122.183105,28.469843 },
		{ "Cypress Flats", 814.442017,-2130.448486,28.867798 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsBS[6] = {
		{ "Paleto Bay", -286.639038,6239.389648,30.567659 },
		{ "Sandy Shores", 1938.357910,3717.808350,31.607185 },
		{ "Havick", -27.791309,-136.863708,56.515392 },
		{ "Rockford Hills", -829.426392,-191.582718,36.921909 },
		{ "Vespucci", -1294.995239,-1117.641724,6.157444 },
		{ "Mirror Park", 1198.025757,-471.814178,65.670250 },
	};

	static struct {
		const char* Name;
		float X;
		float Y;
		float Z;
	} TPLocationsAirport[7] = {
		{ "Los Santos Airport", -1070.906250,-2972.122803,13.773568 },
		{ "Flight School", -1142.084229,-2697.341553,13.324973 },
		{ "Sandy Shores", 1682.196411,3279.987793,40.647972 },
		{ "McKenzie Airfield", -1682.196411,3279.987793,40.647972 },
		{ "Fort Zancudo", -2446.711182,3142.811035,32.194775 },
		{ "Fort Zancudo Front", -1563.743286,2769.382080,16.819347 },
		{ "LS Airport Hangar", -978.708496,-3001.840820,13.317889 },
	};
}
