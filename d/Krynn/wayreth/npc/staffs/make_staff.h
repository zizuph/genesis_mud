/* Staff global design mappings for Bubba in Gelan,
   Coded by Maniac 23.6.95. 
*/

#define STAFF_GREED 235


mapping
staff_metal_rating = (["steel" : 12,
                         "silver" : 9,
                         "wood" : 6 ]);

mapping
staff_length_rating = (["long" : 28,
                          "medium" : 22,
                          "short" : 16 ]);

mapping
staff_length_weight_mult = (["short" : 85,
                               "medium" : 100,
                               "long" : 115]);

mapping
staff_metal_weight_mult = (["steel" : 69,
                              "silver" : 105,
                              "bronze" : 39 ]);

mapping 
staff_name_descs = 
               ([ "fauchard" : "This staff is a single-edged blade " +
                               "mounted on a pole, plus a blade " +
                               "catcher. ", 
                   "halberd" : "This staff has a large axe blade, a " +
                               "spear-head at the end and a hook on the " + 
                               "back. ",
                   "trident" : "This staff is a large, nasty looking " +
                               "three-pronged fork. "
                ]);

mapping
staff_metal_descs =
              ([ "steel" : "Made of steel, ",
                 "silver" : "Made of silver, ",
                 "bronze" : "Made of bronze, " ]);

mapping
staff_length_descs =  
              (["long" : "it is pretty long, about seven feet. ",
                "medium" : "it is of medium length, about six feet. ",
                "short" : "it is quite short, about five feet. " ]);


mapping
staff_decor_descs = 
                ([ "runed" : "It is decorated with unusual looking " +
                             "runes. ",
                   "sleek" : "The haft is narrow and its surface is " +
                             "especially smooth and sleek. ",
                   "fiery" : "The haft is painted with majestic red flames. "
                ]);


/* Function to calculate the wc of made staff, given its metal 
   and length. 
*/
int
query_made_staff_wc(string m, string l)
{
    return (staff_metal_rating[m] + staff_length_rating[l]);
}


/* Function to calculate the pen of made staff, given its metal 
   and length. 
*/
int
query_made_staff_pen(string m, string l)
{
    return (staff_metal_rating[m] + staff_length_rating[l]);
}


/* Function to calculate the made staff value */
int
query_made_staff_value(string m, string l)
{
    int w = query_made_staff_wc(m, l);
    int p = query_made_staff_pen(m, l);
    return F_VALUE_WEAPON(w, p);
}

