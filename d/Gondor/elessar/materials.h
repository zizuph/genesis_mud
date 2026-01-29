#ifndef MATERIAL_H
#define MATERIAL_H

#define M_CORROSION 0
#define M_DULL 1
#define M_BREAK 2
#define M_DENSITY 3
#define M_VALUE 4
#define M_PENMOD 5
#define M_TO_HIT 6

#define M_DEFAULT_MATERIAL_DATA ({10, 10, 10, 765,     100, ({0,0,0}), 0}) 

/* Corrosion, dull, break, density*100, value*100, ({impale,slash,blud}), hit */
/* [0-20]     [0-30] [0-20] */
#define MATERIAL_DATA ([\
    "adamant": ({ 2,  4,  3, 264, 2800000, ({2,1,-3}), 5}), \
    "mithril": ({ 3,  6,  4, 385, 1400000, ({1,1,-2}), 3}), \
    "platinum":({ 5, 10, 10,2130,  120000, ({-2,-3,5}), -5}), \
    "gold":    ({ 2, 30, 10,1930,   10000, ({-2,-2,4}), -4}), \
    "silver":  ({ 5, 25, 15,1051,     400, ({-1,-1,2}), -2}), \
    "steel":   ({ 8,  8,  8, 783,     200, ({0,0,0}), 0}), \
    "iron":    ({10, 10, 10, 765,     100, ({0,0,0}), 0}), \
    "bronze":  ({10, 15, 10, 815,      85, ({0,0,0}), 0}), \
    "brass":   ({10, 18, 10, 855,      70, ({0,0,0}), 0}), \
    "tin":     ({18, 25, 15, 735,      60, ({0,0,0}), 0}), \
    "lead":    ({ 8, 30, 10,1137,      50, ({-2,-2,4}), -3}), \
    "copper":  ({15, 20, 10, 890,      33, ({2,-2,0}), 0}), \
    "oak":     ({ 8, 10, 13,  77,      10, ({0,-2,2}), 1}), \
    "pine":    ({ 8, 10, 15,  43,      10, ({0,-2,2}), 1}), \
    "granite": ({ 3, 10, 12, 157,      50, ({-2,-1,3}), -1}), \
])
#endif
