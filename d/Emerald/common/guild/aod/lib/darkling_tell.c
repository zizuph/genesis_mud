/*
 *  /d/Emerald/common/guild/aod/lib/darkling_tell.c
 *
 *  This module makes it possible to send a given text string into the
 *  functions and have it formatted nicely into a unique spherical
 *  tell.
 *
 *  Created March 2007 by Cooper Sherry (Gorboth)
 *    special thanks to Mercade (as usual!)
 */
#pragma strict_types

/* definitions */
#define        DRAW_CENTER       19

/* prototypes */
public void        darkling_tell(string str, object player, string name);


/*
 * Function name: darkling_tell
 * Description  : The Darklings have a very specific way of communicating 
 *                (basically telepathy.) This function takes a given string
 *                and formats it into the aesthetic of a Darkling tell.
 * Arguments    : string str - the text for the tell
 *                object player - the person receiving the tell
 */
public void
darkling_tell(string str, object player, string name)
{
    string   darkling_txt,
             the_format,
            *middle_text,
            *explode_arr,
             temp_line = "",
            *front_text,
            *back_text;
    int      i,
             back_point,
             front_back,
             front_point,
             median,
             finished = 0,
             current_back,
             current_front;

    string  *left_side = ({
                ".....",
                ".ue@$$$****",
                "ue$$*#\"\"   ",
                "u@$*\"`     ",
                ".o$R\"    ",
                ".@$#`  ",
                "o$#`  ",
                "x$P`  ",
                "d$\"  ",
                "@$\" ",
                "d$  ",
                "d$ ",
                ":$F ",
                "$$ ",
                "x$\" ",
                "$$ ",
                ":$E ",
                "t$' ",
                "@$ ",
                "$$ ",
                "9$ ",
                "?$x ",
                "$$ ",
                "R$: ",
                "'$& ",
                "#$: ",
                "$$ ",
                "'$b ",
                "`$b ",
                "\"$N  ",
                "'*$c  ",
                "\"$N.  ",
                "#$N.  ",
                "`#$Nu   ",
                "\"R$o.    ",
                "^#$$bu.     ",
                "`\"#R$$Wou.... ",
                "`\"\"#***$$",
              });

    string  *right_side = ({
                "..... ",
                "****$$$$Weu.",
                "    `\"\"*$$No.",
                "     \"#$$o.",
                "   \"#$Nu ",
                "   \"$$u ",
                "  \"$$u",
                "  \"$o ",
                "  $$.",
                " #$L",
                " #$c",
                " #$L",
                " $$ ",
                " '$N",
                " #$:",
                " $$",
                " 9$.",
                " '$k",
                " $B",
                " $$",
                " $E",
                " x$!",
                " $$",
                " :$F",
                " @$ ",
                " d$\"",
                " :$P",
                " .$P ",
                " .$$ ",
                " .$P ",
                "  u$# ",
                "  .@$\"",
                "  .@$#",
                "   u@$# ",
                "    ue$R\"",
                "      .uW$P\"`",
                " ....uueW$$*#\" ",
                "$$$***\"\"\"`",
              });

    int    *middle_len = ({
                0,
                0,
                8,
                15,
                25,
                32,
                37,
                41,
                45,
                49,
                51,
                54,
                55,
                56,
                57,
                59,
                59,
                59,
                61,
                61,
                61,
                59,
                59,
                57,
                57,
                55,
                54,
                52,
                50,
                47,
                43,
                39,                
                35,
                29,
                21,
                10,
                0,
                0,
              });

    if (!strlen(str))
    {
        return;
    }

    explode_arr = explode(str, " ");

    for (i = 0; i < sizeof(explode_arr); i++)
    {
        if (strlen(explode_arr[i]) > middle_len[DRAW_CENTER])
        {
            player->catch_tell("Utter nonsense! Try real words, perhaps?\n");
            return;
        }
    }

    middle_text = allocate(sizeof(left_side));
    if (sizeof(explode_arr) == 1)
    {
        middle_text[DRAW_CENTER] = str;
        finished = 1;
    }

    /* if we're finished, then all of this is unnecessary */
    if (!finished)
    {
        /* determine the median index point of the array */
        median = sizeof(explode_arr) / 2; 
        /* Split the text into a front and back end. The back is easiest. */
        back_text = explode_arr[median..];
        /* The trick here is that we want it in reverse order. */
        front_text = allocate(median);
        for (i = 0; i < sizeof(front_text); i++)
        {
            front_text[i] = explode_arr[median - 1 - i];
        }

        i = 0;
        back_point = 0;
        front_point = 0;
        front_back = 0;
 
        /* The next step is to draw the middle line of the circle. This
         * requires alternating between front and back text, adding each
         * respectively either to the front or the back of the string. When
         * the string exceeds the alotted field length, we stop.
         */
        temp_line = "";
        while (strlen(temp_line) < middle_len[DRAW_CENTER])
        {
            if (!strlen(temp_line))
            {
                temp_line = front_text[i];
                middle_text[DRAW_CENTER] = temp_line;

                temp_line += " " + back_text[i];
    
                if (strlen(temp_line) < middle_len[DRAW_CENTER])
                {
                    middle_text[DRAW_CENTER] = temp_line;
                }
            }
            else
            {
                /* Alternate between front and back ... */
                if (front_back)
                {
                    if (i < sizeof(front_text))
                    {
                        temp_line = front_text[i] + " " + temp_line;
                        front_point = i;
                    }
                }
                else
                {
                    if (i)
                    {
                        temp_line += " " + back_text[i];
                    }

                    back_point = i;
                    i++;
                }
                front_back = !front_back;
            }

            if (strlen(temp_line) <= middle_len[DRAW_CENTER])
            {
                middle_text[DRAW_CENTER] = temp_line;
                current_back = back_point;
                current_front = front_point;
            }

            if (i == sizeof(back_text))
            {
                finished = 1; /* we've drawn the entire string */
                /* we've exceeded the array, so lets break the while loop */
                break;
            }
        } /* while (strlen(temp_line) < middle_len[DRAW_CENTER]) */
    } /* if (!finished */

    /* The next few steps are also unnecessary if we have already drawn the
     * entire string. However, we want this in a separate if statement
     * because it functions independantly of the if (!finished) statement
     * above.
     */
    if (!finished)
    {
        if (current_back == back_point)
        {
            back_point++;
        }

        if (current_front == front_point)
        {
            front_point++;
        }
    
        /* Now that the middle line is drawn, assuming there is further
         * length to the string, we want to take the first half of the
         * string as defined by the front_text array and place the words
         * one by one on the lines as they move up from center.
         */
        i = DRAW_CENTER - 1;
        for (; front_point < sizeof(front_text); front_point++)
        {
            temp_line = front_text[front_point]
              + (middle_text[i] ? (" " + middle_text[i]) : "");

            if (strlen(temp_line) < middle_len[i])
            {
                middle_text[i] = temp_line;
            }
            else
            {
                i--;
                middle_text[i] = front_text[front_point];
            }
        }     

        /* Now we repeat the process, but this time drawing the second
         * half of the remaining string and moving down from center within
         * the circle.
         */
        i = DRAW_CENTER + 1;
        for (; back_point < sizeof(back_text); back_point++)
        {
            temp_line = (middle_text[i] ? (middle_text[i] + " ") : "")
              + back_text[back_point];

            if (strlen(temp_line) < middle_len[i])
            {
                middle_text[i] = temp_line;
            }
            else
            {
                i++;
                middle_text[i] = back_text[back_point];
            }
        }  
    } /* if (!finished) */

    /* Now, finally, we draw the circle itself around the formatted
     * string. Nifty effect!
     */
    if (strlen(name))
    {
        player->catch_tell("\n" + sprintf("%|80s",
            "The voice of " + capitalize(name) + " speaks into your"
          + " mind ...\n\n"));
    }
  
    for (i = 0; i < sizeof(left_side); i++)
    {
        if (!middle_text[i])
        {
            middle_text[i] = "";
        }

        the_format = "%-" + strlen(left_side[i]) + "s"
                   + "%|" + middle_len[i] + "s"
                   + "%-" + strlen(right_side[i]) + "s";
        darkling_txt = sprintf(
                           the_format,
                           left_side[i],
                           middle_text[i],
                           right_side[i] + "\n");

//      if (player->query_real_name() != "gorboth")
//      {
//          find_living("gorboth")->catch_tell(
//              sprintf("%|80s", darkling_txt));
//      }

        player->catch_tell(sprintf("%|80s", darkling_txt));
    }
} /* darkling_tell */
