int S_numbers(int number, int digits, int spacing, int y) {

  int space = 14;

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    switch (remainder) {
      case 0:
        addElement(88, spacing, y);
        spacing -= space;
        break;

      case 1:
        spacing += 2;
        addElement(89, spacing, y);
        spacing -= space;
        spacing += 1;
        break;

      case 2:
        addElement(90, spacing, y);
        spacing -= space;
        break;

      case 3:
        addElement(91, spacing, y);
        spacing -= space;
        break;

      case 4:
        spacing -= 2;
        addElement(92, spacing, y);
        spacing -= space;
        //spacing += 3;
        break;

      case 5:
        addElement(93, spacing, y);
        spacing -= space;
        break;

      case 6:
        addElement(94, spacing, y);
        spacing -= space;
        break;

      case 7:
        addElement(95, spacing, y);
        spacing -= space;
        break;

      case 8:
        addElement(96, spacing, y);
        spacing -= space;
        break;

      case 9:
        addElement(97, spacing, y);
        spacing -= space;
        break;

      default:
        // statements
        break;
    }
  }


  return spacing;
}