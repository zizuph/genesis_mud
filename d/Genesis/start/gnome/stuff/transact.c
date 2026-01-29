#include "money.h"
#include "macros.h"

#pragma save_binary

#pragma strict_types

inherit MONEY_FN;

/*
 * This is basically Nick's text().
 */

string
text(int *arr)
{
  string *tarr, coin_str;
  int i, defined;

  tarr = ({ });

  for (i = 0; i < 4; i ++) {
      if (arr[i] > 0) {          
          tarr = ({ arr[i] + " " + MONEY_TYPES[i] }) + tarr;
          if (!coin_str) {
	      if (arr[i] > 1) {
		  coin_str = " coins";
	      } else {
		  coin_str = " coin";
	      }
	  }
      }
  }
  defined = sizeof(tarr);

  if (!defined) {
      return 0;
  }

  if (defined == 1) {
      return tarr[0] + coin_str;
  } else {
      return implode(tarr[0 .. defined - 2], ", ") + " and " +
             tarr[defined - 1] + coin_str;
  }
}

void
handle_fail(int coin, int amount, object from, object to) {
    if (to && move_coins(MONEY_TYPES[coin], amount, from, environment(to))) {
	if (from && interactive(from)) {
	    /*
	      If it's a player's money, DEST it. *guffaw*
	      */
	    move_coins(MONEY_TYPES[coin], amount, from, 0);
	}
    } else {
	if (to && living(to)) {
	    tell_object(to, "You dropped some coins!\n");
	    say(QNAME(to) + " dropped some coins.\n");
	}
    }
}

mixed *mlc(int *from, int *to, int amount, int size);

mixed *
mrc(int *from, int *to, int amount, int size) {
    int    has, payed, i;
    int   *move, *change;
    mixed *sub;

    write("mrc");
    move   = allocate(size + 1);
    change = allocate(size + 1);

    while (amount > has && i <= size) {
	has += from[i] * MONEY_VALUES[i];
	i ++;
    }
    do {
	i --;
	has -= from[i] * MONEY_VALUES[i];
	move[i] = (amount - payed - has + MONEY_VALUES[i] - 1) / MONEY_VALUES[i];
	payed += move[i] * MONEY_VALUES[i];
    } while (payed < amount);
    if (payed == amount) {
	return ({ move, change });
    }

    sub = mlc(to, from, payed - amount, i - 1);
    write (payed - amount + ","+i+","+sizeof(sub[0])+","+intp(sub[0])+"\n");
    if (intp(sub[0])) {
	return ({ -1 });
    }
    for (i = 0; i < sizeof(sub[0]); i ++) {
	move[i]   += sub[1][i];
        change[i] += sub[0][i];
    }
    return ({ move, change });
}




mixed *
mlc(int *from, int *to, int amount, int size) {
    int   *move, *change;
    mixed *sub;
    int    i, chunks;

    write("mlc");

    move   = allocate(size + 1);
    change = allocate(size + 1);

    if (!size) {
	if (from[0] < amount) {
	    return ({ -1 });
	}
	return ({ from[0], 0 });
    }

    for (i = size; i >= 0; i --) {
	chunks = amount / MONEY_VALUES[i];
	if (chunks > from[i]) {
	    chunks = from[i];
	}
	amount -= chunks * MONEY_VALUES[i];
	move[i] = chunks;
    }
    if (!amount) {
	return ({ move, change });
    }

    i = 0;
    while (i <= size && (move[i] > from[i] || amount  > MONEY_VALUES[i])) {
	amount += move[i] * MONEY_VALUES[i];
	move[i] = 0;
	i ++;
    }
    move[i] ++;

    sub = mrc(to, from, MONEY_VALUES[i] - amount, size - 1);
    if (intp(sub[0])) {
	return ({ -1 });
    }
    for (i = 0; i < size - 1; i ++) {
	move[i]   += sub[1][i];
        change[i] += sub[0][i];
    }
    return ({ move, change });
}

varargs int *
transact(int amount, object from, object to, int dir, status test) {
    /*
      dir > 0 means 'from' wants to pay low values to 'to' and
      dir < 0 means 'to' wants high values from 'from'.
      
      If 'from' is zero, we create the money.
      If 'to' is zero, we destruct it.
      
      Errors : Array containing 1 element -
      0  : foo?
      1  : 'from' is not wealthy enough.
      2  : 'to' cannot pay the change.
      */

    int   *from_carr, *move_carr, *to_carr, *change_carr;
    mixed *tmp;
    int    change, i;

    if (!from || !to) {
	return ({ 0 });
    } 

    if (dir < 0) {
	tmp = mlc(what_coins(from), what_coins(to), amount, 3);
    } else {
	tmp = mrc(what_coins(from), what_coins(to), amount, 3);
    }
    if (intp(tmp[0])) {
	return ({ 1 });
    }

    if (!test) {
	for (i = 0; i < 4; i ++) {
	    int diff;
	    diff = tmp[0][i] - tmp[1][i];
	    if (diff > 0) {
		if (move_coins(MONEY_TYPES[i], diff, from, to)) {
		    handle_fail(i, diff, from, to);
		}
	    } else {
		if (move_coins(MONEY_TYPES[i], -diff, to, from)) {
		    handle_fail(i, -diff, to, from);
		}
	    }
	}
    }
    return tmp[0] + tmp[1];
}

