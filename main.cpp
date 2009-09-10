/*
  SVGMin - Aggressive SVG minifier

  Copyright (C) 2009 Ariya Hidayat (ariya.hidayat@gmail.com)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/


#include <QtCore>

#include <iostream>

#include "svgminifier.h"

void showHelp()
{
    std::cout << "Usage:" << std::endl << std::endl;
    std::cout << "svgmin [options] input-file [output-file]" << std::endl << std::endl;
    std::cout << "Options" << std::endl << std::endl;
    std::cout <<  "--auto-format             Indents and add line breaks in the output" << std::endl;
    std::cout <<  "--surpress-prefix=foobar  Remove all tags and attributes which have 'foobar' prefix" << std::endl;
    std::cout <<  "--surpress-metadata       Remove all metadata" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 0;
    }

    QCoreApplication app(argc, argv);

    QString inputFile;
    QString outputFile;

    SvgMinifier minifier;

    for (int i = 1; i < argc; ++i) {
        QString arg = QString::fromLocal8Bit(argv[i]);
        if (arg[0] == '-') {
            arg.remove(0, 1);
            if (arg == "h" || arg == "-help") {
                showHelp();
                return 0;
            }
            if (arg == "-auto-format")
                minifier.setAutoFormat(true);
            if (arg == "-surpress-metadata")
                minifier.addTagExclude("metadata");
            QString check = "-surpress-prefix=";
            if (arg.startsWith(check))
                minifier.addPrefixExclude(arg.mid(check.length(), arg.length()));
        } else {
            if (inputFile.isEmpty())
                inputFile = arg;
            else
                outputFile = arg;
        }
    }

    minifier.setInputFile(inputFile);
    minifier.setOutputFile(outputFile);
    minifier.run();

    return 0;
}
