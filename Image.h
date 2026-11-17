//
//  image.cpp
//  
//
//  Created by Zach on 9/2/26.
//

#include <stdio.h>
#include <vector>

#pragma once

#define NUM_CHANNELS 3
class Image
{
protected:
    int m_height;
    int m_width;
 
    std::vector<int> m_image_data;
    
public:
    
    Image( );
    Image( const int& height, const int& width );
    int getHeight( ) const;
    int getWidth( ) const;
    bool indexValid( const int& row, const int& column, const int& channel ) const;
    int index( const int& row, const int& column, const int& channel ) const;
    int getChannel( const int& row, const int& column, const int& channel ) const;
    void setHeight( const int& height );
    void setWidth( const int& width );
    void setChannel( const int& row, const int& column, const int& channel, const int& value );
};
