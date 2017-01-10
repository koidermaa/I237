/*   Copyright 2017 Kristo Oidermaa

    This file is part of I237 homework project

    I237 homework is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    I237 homework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with I237 homework.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _RFID_H_
#define _RFID_H_

extern void rfid_add_card(const char *user);
extern void rfid_remove_card(const char *user);
extern void rfid_list_cards(void);
extern void doorlock(void);

#endif /* _RFID_H_ */
