<br/>
<div align="center">
  <h3 align="center">Image Filter</h3>
  <p align="center"><i>A C program to apply filters to images</i></p>
</div>

![Output](https://user-images.githubusercontent.com/62847649/204623929-6adfbee7-bde3-4e72-a829-6c5924025f20.jpg)

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about">About</a></li>
    <li><a href="#how-to-run">How To Run</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

## About
An image filter in C to process bitmap (BMP) images and apply grayscale, reflection, blur and Sobel edge detection filters.

## How To Run
Compile with `make filter`.

Usage:  
`./filter -[g|r|b|e] filename.bmp output.bmp`  
where  
`-g` is for greyscale  
`-r` is for reflection  
`-b` is for blur  
`-e` is for edge detection  

## License
Distributed under the MIT License. See `LICENSE` for more information.
