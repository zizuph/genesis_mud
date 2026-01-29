/* 
   Balance checker, measures the combat experience to age ratio of 20 members
   from each guild.

   Coded by Maniac. 18/5/95
*/

#include <ss_types.h>
inherit "/std/object";

#define LIMIT 25
#define BALANCE_DATA "/d/Calia/maniac/misc/balance_data"

mapping sample_data = ([ ]);
static int univ_total;
static int univ_num_player;


void
take_sample()
{
    mixed u, el;
    string gn, pn, s;
    int ratio, i;

    seteuid(getuid());
    restore_object(BALANCE_DATA); 
    u = users();
    
    for (i = 0; i < sizeof(u); i++) {
        if (u[i]->query_wiz_level()) 
            continue;
        if (!(gn = u[i]->query_guild_name_occ())) 
            continue;
        pn = u[i]->query_name();
        if (sscanf(pn, "%sjr", s) == 1)
            continue;
        if (u[i]->query_stat(SS_OCCUP) < 50)
            continue;
        ratio = ((u[i]->query_exp_combat()*10) / u[i]->query_age());
        el = sample_data[gn];
        if (!el) 
            sample_data += ([gn : ([pn : ratio]) ]); 
        else if ((m_sizeof(el) < LIMIT) && !el[pn]) {
            sample_data = m_delete(sample_data, gn);
            el += ([pn : ratio]); 
            sample_data += ([gn : el]);
        }
    }
    save_object(BALANCE_DATA);
}


mixed
tfa(int *vals, int size)
{
    int i, total;

    if ((size-5) < 0) 
        return "na";
    total = 0;
    vals = sort_array(vals);
    for (i=(size-1); i >= (size-5); i--)
        total += vals[i];

    return (total / 5); 
}

mixed
*calculate_stats(mixed el)
{
    int i, *vals, j, n;
    int total, avg, sd;
    mixed top_five_avg;

    total = 0;
    avg = 0;
    sd = 0;

    vals = m_values(el);
    n = sizeof(vals);
    top_five_avg = tfa(vals, n);

    for (i = 0; i < n; i++) {
        total += vals[i];
        univ_num_player++;
        univ_total += vals[i]; 
    }
    avg = total / n;    

    total = 0;
    for (i = 0; i < n; i++) {
        j = vals[i] - avg;
        if (j < 0) 
            j = -j;
        total += j;
    }
    sd = total / n; 

    return ({avg, top_five_avg, sd, n});
}

string 
query_stats()
{
    int i, univ_avg;
    mixed *j;
    string *indexes, str;

    univ_total = 0;
    univ_num_player = 0;
    indexes = m_indexes(sample_data);
    str = "Combat experience to age ratio, details:\n\n";
    for (i = 0; i < sizeof(indexes); i++) {
        j = calculate_stats(sample_data[indexes[i]]);
        str += indexes[i] + ":\n    Sample size: "+j[3]+
               ", average: "+j[0]/10 + "." + j[0]%10 + 
               ", top 5 avg: " +
               ((j[1] == "na") ? "na" : 
                                 ("" + j[1]/10 + "." + j[1]%10)) +
               ", standard dev: " + j[2]/10 + "." + j[2]%10 + ".\n"; 
    } 
    univ_avg = univ_total / univ_num_player;
    str += "\nUniversal average: " + univ_avg/10 + "." + 
              univ_avg%10 + ".\n";
    return str;
}

void
create_object()
{
    int i;
    
    set_alarm(1.0, 900.0, "take_sample");
}

