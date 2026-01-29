
#define SEA_CREATURES "/d/Calia/sea/creatures/"
#define WATER "/d/Gondor/sea/"

#define X_LIMIT 16
#define Y_LIMIT 16
#define Z_LIMIT 5

#define NUM_SECTORS_X 2
#define NUM_SECTORS_Y 2
#define NUM_SECTORS_Z 5

#define X_SECTOR(x) ((x * NUM_SECTORS_X) / X_LIMIT)
#define Y_SECTOR(y) ((y * NUM_SECTORS_Y) / Y_LIMIT)
#define Z_SECTOR(z) ((z * NUM_SECTORS_Z) / Z_LIMIT)
#define SECTOR_PATH(x, y, z) (WATER + "sector_" + X_SECTOR(x) + "_" +\
                              Y_SECTOR(y) + "_" + Z_SECTOR(z) + "/")

