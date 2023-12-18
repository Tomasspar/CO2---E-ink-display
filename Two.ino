void Display_two(void) {



  clearArray();
  statusBar();



  int spacing = 28;
  int space = 3;

  int y = 70;

  int number = ppm_1;
  int digits = 0;



  if (up_to_date_1 == 0) {
    addElement(121, 5, 42);
    spacing = 40;
  }



  if (name_1 != "") {
    writeText(name_1, spacing, 40, 2);
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





  number = ppm_2;
  digits = 0;


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




  spacing = 28;

  if (up_to_date_2 == 0) {
    addElement(121, 5, 187);
    spacing = 40;
  }



  if (name_2 != "") {
    writeText(name_2, spacing, 185, 2);
  }

  y = 215;

  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray_2[i]) {
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




  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////



  bool negative = false;

  if (temp_1 < 0) {
    negative = true;
    temp_1 = temp_1 * (-1);
  }

  y = 40;
  spacing = 305;
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


  if (negative) {
    addElement(116, spacing - 12, y + 18);
  }


  //temperature
  addElement(23, 370, y);


  bool m = preferences.getBool("metric", true);

  if (m) {
    //C
    addElement(21, 331, y + 2);
  } else {
    //F
    addElement(22, 331, y + 2);
  }


  //degree
  addElement(26, 311, y + 2);



  y += 55;

  number = hum_1;
  digits = 0;
  tem = hum_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  spacing = 305;

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
  addElement(24, 367, y - 2);

  //percentage
  addElement(25, 315, y);




  //////////////////////////////////////////////////////////////////////////////////////////



  negative = false;

  if (temp_2 < 0) {
    negative = true;
    temp_2 = temp_2 * (-1);
  }

  y = 185;
  spacing = 305;
  digit = (int)((temp_2 - (int)temp_2) * 10);

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

  number = temp_2;
  digits = 0;
  tem = temp_2;  // create a temporary variable to avoid changing the original number
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


  if (negative) {
    addElement(116, spacing - 12, y + 18);
  }


  //temperature
  addElement(23, 370, y);

  if (m) {
    //C
    addElement(21, 331, y + 2);
  } else {
    //F
    addElement(22, 331, y + 2);
  }

  //degree
  addElement(26, 311, y + 2);




  y += 55;

  number = hum_2;
  digits = 0;
  tem = hum_2;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  spacing = 305;

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
  addElement(24, 367, y - 2);

  //percentage
  addElement(25, 315, y);

  //large_line
  addElement(45, 0, 155);

  //draw();
}
