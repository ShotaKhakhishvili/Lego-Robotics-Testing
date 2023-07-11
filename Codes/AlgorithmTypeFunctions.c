/*
	Igebs Or Integers Shoris Maqsimums.

	@param [int] a		Pirveli Ricxvi.
	@param [int] b    Meore Ricxvi.
	@return [int] Or Integers Shoris Maqsimumi.
*/
int max(int a, int b)
{
	// Tu 'a' Metia An Tolia 'b'-ze, Vabrunebt 'a'-s.
	if(a >= b)
		return a;

	// Sxva Variantshi Vabrunebt 'b'-s.
	return b;
}


/*
	Abrunebs Or Floats Shoris Maqsimums.

	@param [float] a		Pirveli Ricxvi.
	@param [float] b    Meore Ricxvi.
	@return [float] Or Floats Shoris Maqsimumi.
*/
float max(float a, float b)
{
	// Tu 'a' Metia An Tolia 'b'-ze, Vabrunebt 'a'-s.
	if(a >= b)
		return a;

	// Sxva Variantshi Vabrunebt 'b'-s.
	return b;
}

/*
	Igebs Or Integers Shoris Minimums.

	@param [int] a		Pirveli Ricxvi.
	@param [int] b    Meore Ricxvi.
	@return [int] Or Integers Shoris Minimumi.
*/
int min(int a, int b)
{
	// Tu 'a' Naklebia An Tolia 'b'-ze, Vabrunebt 'a'-s.
	if(a <= b)
		return a;

	// Sxva Variantshi Vabrunebt 'b'-s.
	return b;
}


/*
	Abrunebs Or Floats Shoris Minimums.

	@param [float] a		Pirveli Ricxvi.
	@param [float] b    Meore Ricxvi.
	@return [float] Or Floats Shoris Minimumi.
*/
float min(float a, float b)
{
	// Tu 'a' Naklebia An Tolia 'b'-ze, Vabrunebt 'a'-s.
	if(a <= b)
		return a;

	// Sxva Variantshi Vabrunebt 'b'-s.
	return b;
}


/*
	Abrunebs Dros Timer1-is Or Gazomvas Shoris

	[
		Es Punqcia Sachiroa Radgan T1 Aris 16 Bit-iani,
		Shesabamisad Tu Or Gazomvebs Shoris Dro Daemtxva Im Moments Roca T1 Ganicdis Overflow-s (65535 Is Shemdeg 65536 Is Magivrad Xdeba 0),
		Mashin Or Gazomvas Shoris Ubralo Sxvaoba Iqneba Uaryopiti Ricxvi Da Kodis Nawili Imushavebs Xarvezit
	]

	@param [int] time_first						T1-is Pirveli Gazomvdan Migebuli Ricxvi (Miliwamebshi)
	@param [int] time_second					T1-is Meore Gazomvidan Migebuli Ricxvi (Miliwamebshi)
	@return [int] Or Gazomvas Shoris Gasuli Dro

*/
int timer_count(int time_first, int time_second)
{
	// Tu Pirveli gazomili Metia Meoreze, Anu Meorem 16 Bit-is Overflow Ganicada Da Unda Davumatot 65536(2^16) Da Davabrunebt Mat Sxvaobas
	if(time_first > time_second)
		return (time_second + 65536 - time_first);

	// Sxva Shemtxvevashi Ubralod Vabrunebt Magat Sxvaobas
	return time_second - time_first;
}


/*
	Ayovnebs Konkretul Task-s Ragac Droit ( Ara Mtlian Programas )

	@param [int] time 					Dro, Ramdeni Xnitac Gvinda Task-is Sheyovneba (Milisamebshi)
*/
void wait(int time)
{
	int t = 0; // Gasuli Dro

	int t0 = time1(T1); // Sawyisi Dro

	while(t < time) // Imushavebs Manam Sanam Gasuli Dro Naklebia Sasurvel Droze
	{
		t = timer_count(t0, time1(T1)); // Anaxlebs Axlandel Dros
	}
}

void stopWheels()
{
	setMotorSpeed(wheelL, 0);
	setMotorSpeed(wheelR, 0);
}

bool inRange(float a, float b, float r)
{
	// Tu B Aris [a - r; a + r] Range-shi
	if((b >= a - r) && (b <= a + r))
	{
		return true;
	}
	// Sxva Shemtxvevashi
	return false;
}

float MmToEncoder(float Mm)
{
	float MMforEncoder = wheelRadius * 2 * PI / 360;
	return Mm / MMforEncoder;
}

float EncoderToMm(float Enc)
{
	float MMforEncoder = wheelRadius * 2 * PI / 360;
	return Enc * MMforEncoder;
}

float DegToDeltaEncoder(float deg)
{
	float dis = 195; // Borblebs Shoris Mandzili Milimetrebshi
	float r = 28;  // Borblis Radiusi Milimetrebshi

	float L_Rkali = 2 * PI * dis * deg / 360;

	float L_Borbali = 2 * PI * r;

	float Enc = 360 * (L_Rkali / L_Borbali);

	return Enc;
}

float tanh(float x)
{
  float numerator = exp(2 * x) - 1;
 	float denominator = exp(2 * x) + 1;
  return (numerator / denominator);
}
