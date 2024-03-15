#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#define     OK                               0
#define     NOK                              1
#define     NULL                             0

typedef		unsigned char					u8;
typedef		signed char						s8;


typedef		unsigned short int				u16;
typedef		signed short int				s16;


typedef		unsigned long int				u32;
typedef		signed long int					s32;


typedef		unsigned long long int			u64;
typedef		signed long long int			s64;


typedef		float 							f32;

typedef		double							f64;
typedef		long double						f128;

typedef enum
{
	EOK=0,
	ENOK,
	PARAMRETER_OUT_RANGE,
	PARAMERTE_NULL_PTR

}tenuErrrorStatus;



#endif
