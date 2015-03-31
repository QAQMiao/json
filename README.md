# QAQMiao's json parser.


This is a json parser.As we all know that json is a quite common data structure in developing.
So this is my first project's focusing point.

## what can my parser do?
This project can simply do such things : 
- load json files
- load json strings
- judge whether the parsing is successful or not

## supported data types of json

- json strings
- json numbers
- json booleans(true/false)
- json objects
- json arrays

Let's take a glance at some sample:
```json
{
     "name" : "GaoBoyuan",
     "age" : 19,
     "sex" : "male",
     "handsome" : true,
     "girlfirend" : {
              "name" : "miaomiao",
              "sex" : "female",
              "age" : 20,
              "beautiful" : true,
              "hobby" : ["tv operas",1,"pc games","computer science","Roller skating","cou re nao"]
      },
      "hobby" : ["pc games","computer science","music"]
}
```

And the output is :

```xml
<node name="name" type="jsonString">GaoBoyuan</node>
<node name="age" type="jsonNumber">19</node>
<node name="sex" type="jsonString">male</node>
<node name="handsome" type="jsonBoolean">true</node>
<node name="girlfirend" type="jsonObject">
	<node name="name" type="jsonString">miaomiao</node>
	<node name="sex" type="jsonString">female</node>
	<node name="age" type="jsonNumber">20</node>
	<node name="beautiful" type="jsonBoolean">true</node>
	<node name="hobby" type="jsonArray">
		<elem index="0">
			<node name="" type="jsonString">tv operas</node>
		</elem>
		<elem index="1">
			<node name="" type="jsonNumber">1</node>
		</elem>
		<elem index="2">
			<node name="" type="jsonString">pc games</node>
		</elem>
		<elem index="3">
			<node name="" type="jsonString">computer science</node>
		</elem>
		<elem index="4">
			<node name="" type="jsonString">Roller skating</node>
		</elem>
		<elem index="5">
			<node name="" type="jsonString">cou re nao</node>
		</elem>
	</node>
</node>
<node name="hobby" type="jsonArray">
	<elem index="0">
		<node name="" type="jsonString">pc games</node>
	</elem>
	<elem index="1">
		<node name="" type="jsonString">computer science</node>
	</elem>
	<elem index="2">
		<node name="" type="jsonString">music</node>
	</elem>
</node>

```

####此版本暂时仅支持正确格式的json文件的解析
That's all.TKS.
