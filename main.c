#include <stdio.h>
#include <assert.h>
#include "main.h"

static void ColorPairToString(const ColorPair* colorPair, char* buffer) 
{
    sprintf(buffer, "%s and %s",
    MajorColorNames[colorPair->majorColor],
    MinorColorNames[colorPair->minorColor]);
}

static ColorPair GetColorFromPairNumber(int pairNumber) 
{
    ColorPair colorPair;
    int zeroBasedPairNumber = pairNumber - 1;
    colorPair.majorColor = (enum MajorColor)(zeroBasedPairNumber / numberOfMinorColors);
    colorPair.minorColor =(enum MinorColor)(zeroBasedPairNumber % numberOfMinorColors);

    return colorPair;
}

static int GetPairNumberFromColor(const ColorPair* colorPair) 
{
    return colorPair->majorColor * numberOfMinorColors + colorPair->minorColor + 1;
}

void testPairToNumber(enum MajorColor major, enum MinorColor minor, int expectedPairNumber)
{
    ColorPair colorPair;
    colorPair.majorColor = major;
    colorPair.minorColor = minor;
    int pairNumber = GetPairNumberFromColor(&colorPair);
    printf("Pair number %d\n", pairNumber);
    assert(pairNumber == expectedPairNumber);
}

void testNumberToPair(int pairNumber, enum MajorColor expectedMajor, enum MinorColor expectedMinor)
{
    ColorPair colorPair = GetColorFromPairNumber(pairNumber);
    char colorPairNames[MAX_COLORPAIR_NAME_CHARS];
    ColorPairToString(&colorPair, colorPairNames);
    printf("Correspond to twisted pairs %s\n", colorPairNames);
    assert(colorPair.majorColor == expectedMajor);
    assert(colorPair.minorColor == expectedMinor);
}

int main() 
{
    int majorColoridx;
    int minorColoridx;
    static int offset = 1;
    FILE *fp;

    fp = freopen("25Pair_color_code.txt", "w+", stdout);
    if(fp == NULL)
    {
        return 0;
    }
    for (majorColoridx = 0; majorColoridx < 5; majorColoridx++) 
    {
		for (minorColoridx = 0; minorColoridx < 5; minorColoridx++) 
        {
            testPairToNumber(majorColoridx, minorColoridx, (minorColoridx + offset));
            testNumberToPair((minorColoridx + offset), majorColoridx, minorColoridx);
		}
		offset += 5;
	}
    fclose(fp);

    return 0;
}
