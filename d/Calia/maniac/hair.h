/*  Hairstyle include file, goes in the hairdresser and the hair shadow
    in Gelan

    coder(s):   Glykron & Maniac

    History:
          6/5/96       New styles and colours added         Maniac
          9/6/95       New styles and colours added         Maniac

*/

/* Note: It is essential that style, colour and length mapping
         indices are less than 6 letters long, as all three have
         to fit within a string no greater than 20 chars long,
         in the autoshadow_list, including commas.

         Maniac
*/

#define HAIR_STYLES  \
([ \
    "lsho" : "draped over the left shoulder",  \
    "rsho" : "draped over the right shoulder", \
    "flat" : "styled in a flat top", \
    "pigt" : "styled with pigtails", \
    "lobs" : "obscuring the left eye", \
    "robs" : "obscuring the right eye", \
    "pull" : "half pulled out", \
    "bush" : "bushido style", \
    "norm" : "normal", \
    "mat" : "matted", \
    "bmid" : "bald in the middle", \
    "fbra" : "tied into a french braid", \
    "bra" : "braided", \
    "bmat" : "matted with blood", \
    "unk" : "very wild and unkempt", \
    "wind" : "windswept", \
    "str" : "straight", \
    "moh" : "mohawk style", \
    "tied": "tied back", \
    "spk" : "spiked like a porcupine", \
    "rpart" : "parted on the right", \
    "lpart" : "parted on the left", \
    "cpart" : "parted down the centre",  \
    "dlock" : "styled into dreadlocks", \
    "tail" : "styled with a pony tail", \
    "tknot" : "styled with a top-knot", \
    "swirl" : "swirled into a bun", \
    "crimp" : "crimped along the side", \
    "bangs" : "combed down in bangs", \
    "punk" : "sticking straight up", \
    "burn" : "burned into wisps",  \
    "wavy" : "wavy",  \
    "curly" : "curly", \
    "tcur" : "tight curled", \
    "lcur" : "loose curled", \
    "swept" : "swept back",  \
    "layer" : "feathered back into layers" \
]) 


#define HAIR_LENGTHS \
([ \
    "vsh" : "very short", \
    "sht" : "short", \
    "med" : "medium length", \
    "neck": "neck length", \
    "shd" : "shoulder length", \
    "waist" : "waist length", \
    "hip" : "hip length",  \
])

#define HAIR_COLOURS \
([ \
   "lgr" : "light grey", \
   "dgr" : "dark grey", \
   "sbl" : "strawberry blond", \
   "pbl" : "platinum blond", \
   "blond" : "blond", \
   "gold" : "golden", \
   "lbr" : "light brown", \
   "gbr" : "golden brown", \
   "dbr" : "dark brown", \
   "ches" : "chestnut coloured", \
   "aub" : "auburn", \
   "black" : "black", \
   "rbl"  : "raven black", \
   "jbl" : "jet black", \
   "red" : "red", \
   "dpr" : "deep red", \
   "flr" : "flame red", \
   "ging" : "ginger", \
   "green" : "green", \
   "ora" : "orange", \
   "blue" : "blue", \
   "lbe" : "light blue", \
   "dbe" : "dark blue", \
   "purp" : "purple", \
   "dpur" : "deep purple", \
   "white" : "white", \
   "sil" : "silvery", \
   "crim" : "crimson" \
])

