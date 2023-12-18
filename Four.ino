void Display_four(void) {


  int spacing = 10;
  int space = 3;
  int y = 100;
  int number = ppm_1;
  int digits = 0;


  clearArray();
  statusBar();


  if (up_to_date_1 == 0) {
    addElement(121, 160, 45);
  }

  if (name_1 != "") {
    writeText(name_1, spacing, 50, 2);
  }



  int tem = ppm_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  int ppmArray_1[digits];

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    ppmArray_1[i] = remainder;
  }






  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray_1[i]) {
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




  bool m = preferences.getBool("metric", true);

  if (m) {
    //C
    addElement(111, 10, y - 22);
  } else {
    //F
    addElement(112, 10, y - 22);
  }





  bool negative = false;

  if (temp_1 < 0) {
    negative = true;
    temp_1 = temp_1 * (-1);
  }

  space = 13;
  spacing = 182;
  int digit = (int)((temp_1 - (int)temp_1) * 10);






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

  number = temp_1;
  digits = 0;
  tem = temp_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }



  int x = S_numbers(number, digits, spacing, y);

  if (negative) {
    addElement(99, x + 2, y + 10);
  }




  number = hum_1;

  spacing = 182;
  y = 130;

  digits = 0;
  tem = hum_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  x = S_numbers(number, digits, spacing, y);

















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




  y = 98;
  spacing = 210;
  space = 3;


  if (up_to_date_2 == 0) {
    addElement(121, 360, 45);
  }

  if (name_2 != "") {
    writeText(name_2, spacing, 50, 2);
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
    addElement(111, 210, y - 20);
  } else {
    //F
    addElement(112, 210, y - 20);
  }




  negative = false;

  if (temp_2 < 0) {
    negative = true;
    temp_2 = temp_2 * (-1);
  }

  space = 13;
  spacing = 380;
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

  x = S_numbers(number, digits, spacing, y);


  if (negative) {
    addElement(99, x + 2, y + 10);
  }



  number = hum_2;

  spacing = 380;
  y = 130;

  digits = 0;
  tem = hum_2;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  x = S_numbers(number, digits, spacing, y);



















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




  y = 233;
  spacing = 10;
  space = 3;


  if (up_to_date_3 == 0) {
    addElement(121, 160, 180);
  }

  if (name_3 != "") {
    writeText(name_3, spacing, 185, 2);
  }





  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray_3[i]) {
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
    addElement(111, 10, y - 20);
  } else {
    //F
    addElement(112, 10, y - 20);
  }


  negative = false;

  if (temp_3 < 0) {
    negative = true;
    temp_3 = temp_3 * (-1);
  }

  space = 13;
  spacing = 182;
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




  number = hum_3;

  spacing = 182;
  y = 263;

  digits = 0;
  tem = hum_3;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  x = S_numbers(number, digits, spacing, y);















  digits = 0;

  number = ppm_4;

  tem = ppm_4;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  int ppmArray_4[digits];

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    ppmArray_4[i] = remainder;
  }




  y = 233;
  spacing = 210;
  space = 3;


  if (up_to_date_4 == 0) {
    addElement(121, 360, 180);
  }

  if (name_4 != "") {
    writeText(name_4, spacing, 185, 2);
  }






  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray_4[i]) {
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
    addElement(111, 210, y - 20);
  } else {
    //F
    addElement(112, 210, y - 20);
  }


  negative = false;

  if (temp_4 < 0) {
    negative = true;
    temp_4 = temp_4 * (-1);
  }


  space = 13;
  spacing = 380;
  digit = (int)((temp_4 - (int)temp_4) * 10);






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

  number = temp_4;
  digits = 0;
  tem = temp_4;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  x = S_numbers(number, digits, spacing, y);


  if (negative) {
    addElement(99, x + 2, y + 10);
  }






  number = hum_4;
  spacing = 380;
  y = 263;


  digits = 0;
  tem = hum_4;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  x = S_numbers(number, digits, spacing, y);





  addElement(46, 0, 164);

  addElement(113, 199, 166);
  addElement(113, 199, 40);
}
