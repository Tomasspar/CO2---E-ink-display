
void Display_three(void) {


  int spacing = 28;
  int space = 3;

  // int y = 65;
  int y = 80;


  int number = ppm_1;
  int digits = 0;


  clearArray();
  statusBar();

  if (up_to_date_1 == 0) {
    addElement(121, 185, 8);
    spacing = 40;
  }


  if (name_1 != "") {
    writeText(name_1, spacing, 50, 2);
  }




  int tem = ppm_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  int ppmArray[digits];

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    ppmArray[i] = remainder;
  }



  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray[i]) {
      case 0:
        addElement(0, spacing, y);
        spacing += 39;
        spacing += 5;
        break;
      case 1:
        addElement(1, spacing, y);
        spacing += 26;
        spacing += 5;
        break;
      case 2:
        addElement(2, spacing, y);
        spacing += 38;
        spacing += 5;
        break;
      case 3:
        addElement(3, spacing, y);
        spacing += 38;
        spacing += 5;
        break;
      case 4:
        addElement(4, spacing, y);
        spacing += 46;
        spacing += 5;
        break;
      case 5:
        addElement(5, spacing, y);
        spacing += 39;
        spacing += 5;
        break;
      case 6:
        addElement(6, spacing, y);
        spacing += 39;
        spacing += 5;
        break;
      case 7:
        addElement(7, spacing, y);
        spacing += 37;
        spacing += 5;
        break;
      case 8:
        addElement(8, spacing, y);
        spacing += 39;
        spacing += 5;
        break;
      case 9:
        addElement(9, spacing, y);
        spacing += 39;
        spacing += 5;
        break;
      default:
        // statements
        break;
    }
  }






  y = 50;
  spacing = 285;
  int digit = (int)((temp_1 - (int)temp_1) * 10);

  switch (digit) {
    case 0:
      spacing -= 19;
      addElement(10, spacing, y);
      spacing -= space;
      break;
    case 1:
      spacing -= 13;
      addElement(11, spacing, y);
      spacing -= space;
      break;
    case 2:
      spacing -= 18;
      addElement(12, spacing, y);
      spacing -= space;
      break;
    case 3:
      spacing -= 19;
      addElement(13, spacing, y);
      spacing -= space;
      break;
    case 4:
      spacing -= 22;
      addElement(14, spacing, y);
      spacing -= space;
      break;
    case 5:
      spacing -= 18;
      addElement(15, spacing, y);
      spacing -= space;
      break;
    case 6:
      spacing -= 19;
      addElement(16, spacing, y);
      spacing -= 5;
      break;
    case 7:
      spacing -= 18;
      addElement(17, spacing, y);
      spacing -= space;
      break;
    case 8:
      spacing -= 19;
      addElement(18, spacing, y);
      spacing -= space;
      break;
    case 9:
      spacing -= 19;
      addElement(19, spacing, y);
      spacing -= space;
      break;
    default:
      // statements
      break;
  }

  spacing -= 7;
  //dot
  addElement(20, spacing, y + 30);
  spacing -= space;

  number = temp_1;
  digits = 0;
  tem = temp_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }



  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    switch (remainder) {
      case 0:
        spacing -= 19;
        addElement(10, spacing, y);
        spacing -= space;
        break;
      case 1:
        spacing -= 13;
        addElement(11, spacing, y);
        spacing -= space;
        break;
      case 2:
        spacing -= 18;
        addElement(12, spacing, y);
        spacing -= space;
        break;
      case 3:
        spacing -= 19;
        addElement(13, spacing, y);
        spacing -= space;
        break;
      case 4:
        spacing -= 22;
        addElement(14, spacing, y);
        spacing -= space;
        break;
      case 5:
        spacing -= 18;
        addElement(15, spacing, y);
        spacing -= space;
        break;
      case 6:
        spacing -= 19;
        addElement(16, spacing, y);
        spacing -= 5;
        break;
      case 7:
        spacing -= 18;
        addElement(17, spacing, y);
        spacing -= space;
        break;
      case 8:
        spacing -= 19;
        addElement(18, spacing, y);
        spacing -= space;
        break;
      case 9:
        spacing -= 19;
        addElement(19, spacing, y);
        spacing -= space;
        break;
      default:
        // statements
        break;
    }
  }

  //temperature
  addElement(23, 350, y);


  bool m = preferences.getBool("metric", true);

  if (m) {
    //C
    addElement(21, 311, y + 2);
  } else {
    //F
    addElement(22, 311, y + 2);
  }


  //degree
  addElement(26, 291, y + 2);



  y += 55;

  number = hum_1;
  digits = 0;
  tem = hum_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  spacing = 285;

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    switch (remainder) {
      case 0:
        spacing -= 19;
        addElement(10, spacing, y);
        spacing -= space;
        break;
      case 1:
        spacing -= 13;
        addElement(11, spacing, y);
        spacing -= space;
        break;
      case 2:
        spacing -= 18;
        addElement(12, spacing, y);
        spacing -= space;
        break;
      case 3:
        spacing -= 19;
        addElement(13, spacing, y);
        spacing -= space;
        break;
      case 4:
        spacing -= 22;
        addElement(14, spacing, y);
        spacing -= space;
        break;
      case 5:
        spacing -= 18;
        addElement(15, spacing, y);
        spacing -= space;
        break;
      case 6:
        spacing -= 19;
        addElement(16, spacing, y);
        spacing -= space;
        break;
      case 7:
        spacing -= 18;
        addElement(17, spacing, y);
        spacing -= 5;
        break;
      case 8:
        spacing -= 19;
        addElement(18, spacing, y);
        spacing -= space;
        break;
      case 9:
        spacing -= 19;
        addElement(19, spacing, y);
        spacing -= space;
        break;
      default:
        // statements
        break;
    }
  }

  //humidity
  addElement(24, 347, y - 2);

  //percentage
  addElement(25, 295, y);











  digits = 0;

  number = ppm_2;

  tem = ppm_2;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  int ppmArray_2[digits];

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    ppmArray_2[i] = remainder;
  }




  y = 223;
  spacing = 10;
  space = 3;

  if (up_to_date_2 == 0) {
    addElement(121, 85, 170);
  }

  if (name_2 != "") {
    writeText(name_2, spacing, 195, 3);
  }





  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray_2[i]) {
      case 0:
        addElement(101, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 1:
        addElement(102, spacing, y);
        spacing += 22;
        spacing += space;
        break;
      case 2:
        addElement(103, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 3:
        addElement(104, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 4:
        addElement(105, spacing, y);
        spacing += 35;
        spacing += space;
        break;
      case 5:
        addElement(106, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 6:
        addElement(107, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 7:
        addElement(108, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 8:
        addElement(109, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 9:
        addElement(110, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      default:
        // statements
        break;
    }
  }








  // temp_2 = 114.4;


  bool negative = false;

  if (temp_2 < 0) {
    negative = true;
    temp_2 = temp_2 * (-1);
  }

  space = 13;
  spacing = 182;
  digit = (int)((temp_2 - (int)temp_2) * 10);






  switch (digit) {
    case 0:
      addElement(88, spacing, y);
      spacing -= space;
      break;
    case 1:
      spacing += 3;
      addElement(89, spacing, y);
      spacing -= space;
      spacing += 3;
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
      addElement(92, spacing, y);
      spacing -= space;
      spacing += 3;
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


  //dot
  addElement(98, spacing + 5, y + 16);
  spacing -= 10;

  number = temp_2;
  digits = 0;
  tem = temp_2;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }



  int x = S_numbers(number, digits, spacing, y);

  if (negative) {
    addElement(99, x + 2, y + 10);
  }






  //hum_2 = 41;
  number = hum_2;

  space = 16;
  spacing = 182;
  y = 253;

  digits = 0;
  tem = hum_2;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  x = S_numbers(number, digits, spacing, y);
















  // ppm_3 = 1234;

  digits = 0;

  number = ppm_3;

  tem = ppm_3;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  int ppmArray_3[digits];

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    ppmArray_3[i] = remainder;
  }




  y = 223;
  spacing = 210;
  space = 3;

  if (up_to_date_3 == 0) {
    addElement(121, 285, 170);
    //spacing = 238;
  }

  if (name_3 != "") {
    writeText(name_3, spacing, 195, 3);
  }






  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray_2[i]) {
      case 0:
        addElement(101, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 1:
        addElement(102, spacing, y);
        spacing += 22;
        spacing += space;
        break;
      case 2:
        addElement(103, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 3:
        addElement(104, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 4:
        addElement(105, spacing, y);
        spacing += 35;
        spacing += space;
        break;
      case 5:
        addElement(106, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 6:
        addElement(107, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 7:
        addElement(108, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 8:
        addElement(109, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      case 9:
        addElement(110, spacing, y);
        spacing += 30;
        spacing += space;
        break;
      default:
        // statements
        break;
    }
  }




  if (m) {
    //C
    addElement(111, 116, y - 22);
    addElement(111, 313, y - 22);
  } else {
    //F
    addElement(112, 116, y - 22);
    addElement(112, 313, y - 22);
  }




  negative = false;

  if (temp_3 < 0) {
    negative = true;
    temp_3 = temp_3 * (-1);
  }

  space = 13;
  spacing = 380;
  digit = (int)((temp_3 - (int)temp_3) * 10);






  switch (digit) {
    case 0:
      addElement(88, spacing, y);
      spacing -= space;
      break;
    case 1:
      spacing += 3;
      addElement(89, spacing, y);
      spacing -= space;
      spacing += 3;
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
      addElement(92, spacing, y);
      spacing -= space;
      spacing += 3;
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


  //dot
  addElement(98, spacing + 5, y + 16);
  spacing -= 10;

  number = temp_3;
  digits = 0;
  tem = temp_3;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  x = S_numbers(number, digits, spacing, y);


  if (negative) {
    addElement(99, x + 2, y + 10);
  }






  // hum_3 = 41;
  number = hum_3;

  space = 16;
  spacing = 380;
  y = 253;


  digits = 0;
  tem = hum_3;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  x = S_numbers(number, digits, spacing, y);




  addElement(46, 0, 164);
  addElement(113, 199, 166);
}
