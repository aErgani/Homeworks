#include <stdio.h>

int main()
{
    int
    i,j,
    attempt = 10,
    boardHeight = 300,
    boardWidth = 200,
    areaHeight = 15,
    areaWidth = 20,
    markerHeight = 20,
    markerWidth = 20,
    areaUpLeftX = 100,
    areaUpLeftY = 100,
    userMoveX,
    userMoveY,
    tempUpLeftX,
    tempUpLeftY,
    newUpLeftX,
    newUpLeftY,
    newDownRightX,
    newDownRightY,
    checkHit,
    firstHit;

    printf("Board = [%d x %d], Marked Region = [%d , %d], Detector = [%d , %d]\n",
           boardWidth,boardHeight,areaWidth,areaHeight,markerWidth,markerHeight);
    while(1)
    {
        checkHit = 0;                                       /*assigning the necessary integers "0" to initialize "move"*/
        firstHit = 0;
        printf("Enter the X coordinate of the move\n");     /*getting the coordinates*/
        scanf("%d", &userMoveX);
        printf("Enter the Y coordinate of the move\n");
        scanf("%d", &userMoveY);
        if (userMoveX - (markerWidth-1)/2 < 0 || userMoveX + (markerWidth-1)/2 > boardWidth)            /*checking if the move is legal*/
        {
            printf("Error, move is not valid. Try again. Attempts remaining: %d\n", attempt);
        }
        else if (userMoveY - (markerHeight-1)/2 < 0 || userMoveY + (markerHeight-1)/2 > boardHeight)
        {
            printf("Error, move is not valid. Try again. Attempts remaining: %d\n", attempt);
        }
        else
        {
            printf("LEGAL MOVE\n");
            tempUpLeftX = userMoveX - markerWidth/2;                /*These are the coordiantes of the top left corner of the detector */
            tempUpLeftY = userMoveY + markerHeight/2;
            for (i = tempUpLeftX; i <= tempUpLeftX + 20; i++)       /*We start from that corner and scan whole detector's field*/
                {
                for (j = tempUpLeftY; j >= tempUpLeftY - 20 ; j--)
                {
                    if (i >= areaUpLeftX && i <= areaUpLeftX + areaWidth && j <= areaUpLeftY && j >= areaUpLeftY - areaHeight)      /*while scanning we check if the coordinate we are currently scanning is in the targeted area*/
                    {
                        checkHit++;
                        if(firstHit == 0)           /*this part helps us in partial hit procedure*/
                        {
                            firstHit = 1;           /*this coordinates are the top left corner of the intersected area*/
                            newUpLeftX = i;
                            newUpLeftY = j;
                        }
                        newDownRightX = i;          /*and these are the bottom right corner of the intersected area*/
                        newDownRightY = j;
                    }
                }
            }
            attempt--;
            if (checkHit > 0)                                           /*means we hit something*/
            {
                if (checkHit == (areaHeight + 1) * (areaWidth + 1))     /*this is the whole field of the targeted area so if we hit this much coordinate, it means we won*/
                {
                    printf("CONGRATULATIONS YOU WIN\n");
                    break;
                }
                else                                                    /*we did not hit as much as we should so, initiating PARTIAL HIT PROCEDURE*/
                {
                    areaUpLeftX = newUpLeftX;
                    areaUpLeftY = newUpLeftY;
                    areaHeight = newUpLeftY - newDownRightY;
                    areaWidth = newDownRightX - newUpLeftX;
                    markerHeight = markerHeight/2;
                    markerWidth = markerWidth/2;
                    printf("Partial hit! marked region was shirked to [%d x %d], detector was shirked to [%d x %d]\n",areaWidth,areaHeight,markerWidth,markerHeight);
                }
            }
            printf("attempts remaining : %d\n",attempt);                /*printing the remaining attempts once every legal move*/
        }
    }

    return 0;
}
