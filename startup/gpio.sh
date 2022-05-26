BASE_GPIO_PATH=/sys/class/gpio

exportPin()
{
  if [ ! -e $BASE_GPIO_PATH/gpio$1 ]; then
    echo "$1" > $BASE_GPIO_PATH/export
  fi
}

setOutput()
{
  echo "out" > $BASE_GPIO_PATH/gpio$1/direction
}

setState()
{
  echo $2 > $BASE_GPIO_PATH/gpio$1/value
}
