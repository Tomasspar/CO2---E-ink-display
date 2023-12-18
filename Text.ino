void writeText(String text, int posX, int posY, int dongles) {

  int x = posX;
  int spacing = 15;


  for (int i = 0; i < text.length(); i++) {

    switch (text[i]) {
      case 'A':
        addElement(62, x, posY);
        x += spacing + 1;
        break;

      case 'B':
        addElement(63, x, posY);
        x += spacing;
        break;

      case 'C':
        addElement(64, x, posY);
        x += spacing;
        break;

      case 'D':
        addElement(65, x, posY);
        x += spacing;
        break;

      case 'E':
        addElement(66, x, posY);
        x += spacing - 2;
        break;

      case 'F':
        addElement(67, x, posY);
        x += spacing - 2;
        break;

      case 'G':
        addElement(68, x, posY);
        x += spacing;
        break;

      case 'H':
        addElement(69, x, posY);
        x += spacing;
        break;

      case 'I':
        addElement(70, x, posY);
        x += spacing - 8;
        break;

      case 'J':
        addElement(71, x, posY);
        x += spacing - 1;
        break;

      case 'K':
        addElement(72, x, posY);
        x += spacing;
        break;

      case 'L':
        addElement(73, x, posY);
        x += spacing - 3;
        break;

      case 'M':
        addElement(74, x, posY);
        x += spacing + 4;
        break;

      case 'N':
        addElement(75, x, posY);
        x += spacing;
        break;

      case 'O':
        addElement(76, x, posY);
        x += spacing;
        break;

      case 'P':
        addElement(77, x, posY);
        x += spacing;
        break;

      case 'Q':
        addElement(78, x, posY);
        x += spacing;
        break;

      case 'R':
        addElement(79, x, posY);
        x += spacing;
        break;

      case 'S':
        addElement(80, x, posY);
        x += spacing - 1;
        break;

      case 'T':
        addElement(81, x, posY);
        x += spacing - 1;
        break;

      case 'U':
        addElement(82, x, posY);
        x += spacing;
        break;

      case 'V':
        addElement(83, x, posY);
        x += spacing + 2;
        break;

      case 'W':
        addElement(84, x, posY);
        x += spacing + 9;
        break;

      case 'X':
        addElement(85, x, posY);
        x += spacing;
        break;

      case 'Y':
        addElement(86, x, posY);
        x += spacing;
        break;

      case 'Z':
        addElement(87, x, posY);
        x += spacing;
        break;

      case '0':
        addElement(88, x, posY);
        x += spacing - 1;
        break;

      case '1':
        addElement(89, x, posY);
        x += spacing - 5;
        break;

      case '2':
        addElement(90, x, posY);
        x += spacing;
        break;

      case '3':
        addElement(91, x, posY);
        x += spacing - 1;
        break;

      case '4':
        addElement(92, x, posY);
        x += spacing + 1;
        break;

      case '5':
        addElement(93, x, posY);
        x += spacing;
        break;

      case '6':
        addElement(94, x, posY);
        x += spacing - 1;
        break;

      case '7':
        addElement(95, x, posY);
        x += spacing;
        break;

      case '8':
        addElement(96, x, posY);
        x += spacing;
        break;

      case '9':
        addElement(97, x, posY);
        x += spacing;
        break;

      case '.':
        addElement(98, x, posY + 16);
        x += spacing - 8;
        break;

      case '-':
        addElement(99, x, posY + 10);
        x += spacing - 4;
        break;

      case ':':
        x += spacing - 8;
        break;

      case ' ':
        x += spacing - 8;
        break;

      default:
        x += spacing;
        break;
    }


    if (i == 20 && dongles == 1 && i+1 != text.length()) {
      addElement(98, x, posY + 16);
      x += spacing - 8;
      addElement(98, x, posY + 16);
      x += spacing - 8;
      addElement(98, x, posY + 16);
      break;
    }

    if (i == 7 && dongles == 2 && i+1 != text.length()) {
      addElement(98, x, posY + 16);
      x += spacing - 8;
      addElement(98, x, posY + 16);
      x += spacing - 8;
      addElement(98, x, posY + 16);
      break;
    }

    if (i == 4 && dongles == 3 && i+1 != text.length()) {
      addElement(98, x, posY + 16);
      x += spacing - 8;
      addElement(98, x, posY + 16);
      x += spacing - 8;
      addElement(98, x, posY + 16);
      break;
    }
  }
}